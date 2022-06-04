#include <thread>
#include <iostream>

int x;

// std::atomic
// volatile -- BAN
// sig_atomic_t -- BAN

// std::mutex
// std::thread
// std::condvar

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

class Stack {
    struct Node {
        int value;
        std::atomic<Node *> next;
    }

    std::atomic<Node *> head_{};

public:
    Stack() = defalut;



    void Push(int value) {
        Node * node = new Node{value, head_.load()};
        while (!head_.compare_exchange_strong(node->next, node)) {
        }
    }

    std::optional<int> TryPop() {
        while (true) {
            Node* returned = head_.load();
            if (returned == nullptr) {
                return std::nullopt;
            }
            if (!head_.compare_exchange_strong(returned_, returned_->next)) {
                continue;
            }
            int val = returned_->value;
            // delete returned_;
            return val;
        }
    }
}


int main() {
    std::thread t([]() -> void {
        x = 2;
        std::cout << std::this_thread::get_id() << std::endl;
    });
    t.join();
//    t.detach();

    std::cout << x << std::endl;
}
