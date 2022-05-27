double f(double);
double bound_f(double l, double r);  /// for each i in [l, r] f(i) >= bound_f(l, r)

double p_x = 0.001;

double simple_solve(double l, double r) {
    double m = f(l);
    for (double i = l; i <= r; i += p_x) {
        m = min(m, f(i));
    }
    return m;
}

class TSolver {
public:
    TSolver() {
        answers.reserve(threads);
    }

    double solve(double l, double r) {
        answers.clear();
        double window_size = (r - l) / threads + p_x;
        for (double i = l; i <= r; i += window_size) {
            answers.push_back(std::async([left_border=i,right_border=i+window_size]{
                return simple_solve(left_border, right_border);
            }));
        }
        double ans = f(l);
        for (auto& job : answers) {
            ans = std::min(ans, job.get());
        }
        return ans;
    }

private:
    const size_t threads_ = std::hardware_concurrency();
    std::vector<std::future<double>> answers_;
};

class BBSolver {
public:
    struct AnswerState {
        void test_and_set(double p_new, double v_new) {
            if (value.load(std::memory_order::relaxed) < v_new) {
                return;
            }
            std::unique_lock lock(mx);
            // HERE
            if (value.load(std::memory_order::relaxed) < v_new) {
                return;
            }
            point = p_new;
            value.store(v_new, std::memory_order::relaxed);
        }

        double min() {
            return value.load(std::memory_order::relaxed);
        }

        std::pair<double, double> final_get() {
            return {point.load(std::memory_order::relaxed), value.load(std::memory_order::relaxed)};
        }

        std::mutex mx;  // spinlock
        // std::atomic<bool> spinlock;
        double point;
        std::atomic<double> value;
    } state;

    struct Task {
        double l;
        double r;

        double Size() const {
            return r - l;
        }

        std::pair<Task, Task> Split() const {
            double mid = l + r / 2;
            return {{l, mid}, {mid, r}};
        }
    };

    struct Queue {
        void Put(Task task);
        Task Get();

        std::mutex mx;
        std::vector<Task> task;
    } queue;

    BBSolver() {
        answers.reserve(threads);
    }


    // returns point
    double solve(double l, double r) {
        queue.Put({l, r});
        while (threds_--) {
            answer_.emplace_back([this](){
                run();
            }});
    }
    for (auto && t : answer_) {
        t.join();
    }
    return state.final_get().first;
}

private:
double run() {
    while (!stop) {
        auto task = queue.Get();
        while (true) {
            auto bounded = bound_f(task.l, task.r);
            if (state.min() < bounded) {
                break;
            }
            if (task.Size() < p_x) {
                auto value = f(task.l);
                state.test_and_set(task.l, value);
                break;
            }
            auto [f, s] = task.Split();
            queue.Put(std::move(s));
            task = std::move(f);
        }
    }
}

bool stop_ = false;
size_t threads_ = std::hardware_concurrency();
std::vector<std::thread> answers_;
};


template <typename T>
class MPMCBoundedQueue {
public:
    struct Node {
        alignas(64) std::atomic_int counter = 0;
        T value{};
    };

    explicit MPMCBoundedQueue(int size) : factor_(size - 1), buffer_(size) {
        for (int i = 0; i < size; ++i) {
            buffer_[i].counter.store(i);
        }
    }

    bool Enqueue(T value) {
        int factor = factor_;
        while (true) {
            int local_end = end_;
            Node* node = &buffer_[local_end & factor];
            int diff = node->counter - local_end;
            if (diff == 0) {
                if (end_.compare_exchange_strong(local_end, local_end + 1)) {
                    node->value = std::move(value);
                    node->counter.store(local_end + 1);
                    return true;
                }
            } else if (diff < 0) {
                return false;
            }
        }
    }

    bool Dequeue(T& data) {
        int factor = factor_;  // i waannnnnnnnnntttttttttt moooooooorreeeeeeeeeeee speeeeeeeeed
        while (true) {
            int local_start = start_;
            Node* node = &buffer_[local_start & factor];
            int diff = node->counter - local_start;
            if (diff == 1) {
                if (start_.compare_exchange_strong(local_start, local_start + 1)) {
                    data = std::move(node->value);
                    node->counter.store(local_start + factor + 1);
                    return true;
                }
            } else if (diff < 1) {
                return false;
            }
        }
    }

private:
    alignas(64) int factor_ = 0;
    alignas(64) std::atomic_int start_ = 0;
    alignas(64) std::atomic_int end_ = 0;
    alignas(64) std::vector<Node> buffer_;
};

