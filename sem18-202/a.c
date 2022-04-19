/// Посчитать Pi методом монте-карло при ограничении в 5 секунд

#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

volatile int flag = 1;

void handler(int sig) {
    flag = 0;
}

long long sq_dist (int i, int j) {
    long long a = (1ll * RAND_MAX / 2 - i) * (1ll * RAND_MAX / 2 - i);
    long long b = (1ll * RAND_MAX / 2 - j) * (1ll * RAND_MAX / 2 - j);
    return a + b;
}

int main() {
    int in_circle = 0, all = 0;
    // srand(time(NULL));
    srand(42);

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0 | SA_RESTART;
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval new_val = {
            .it_value = {
                    .tv_sec = 2,
                    .tv_usec = 980000
            }
    };
    setitimer(ITIMER_REAL, &new_val, NULL);

    while (flag) {
        int i = rand(), j = rand();
        ++all;
        if (sq_dist(i, j) <= 1ll * RAND_MAX * RAND_MAX / 4) {
            ++in_circle;
        }
    }
    double pi = 4. * in_circle / all;
    printf("%lf\n", pi);
}
