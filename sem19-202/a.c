/// Посчитать Pi методом монте-карло при ограничении в 5 секунд

#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <inttypes.h>

long long sq_dist (int i, int j) {
    long long a = (1ll * RAND_MAX / 2 - i) * (1ll * RAND_MAX / 2 - i);
    long long b = (1ll * RAND_MAX / 2 - j) * (1ll * RAND_MAX / 2 - j);
    return a + b;
}

int main() {
    int in_circle = 0, all = 0;
    // srand(time(NULL));
    srand(42);

    struct itimerspec new_val = {
            .it_value = {
                    .tv_sec = 2,
                    .tv_nsec = 980000000
            }
    };

    int tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    timerfd_settime(tfd, 0, &new_val, NULL);
    uint64_t buf;

    while (read(tfd, &buf, sizeof(buf)) != 8) {
        int i = rand(), j = rand();
        ++all;
        if (sq_dist(i, j) <= 1ll * RAND_MAX * RAND_MAX / 4) {
            ++in_circle;
        }
    }
    double pi = 4. * in_circle / all;
    printf("%lf\n", pi);
}
