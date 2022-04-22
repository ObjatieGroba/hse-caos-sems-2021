#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/timerfd.h>
#include <unistd.h>

typedef struct Point {
    int x, y;
} Point;

#define sqr(a) ((int64_t)(a) * (a))

int64_t sq_distance(Point a, Point b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

const int64_t radius = RAND_MAX / 2;
const Point center = {.x = radius, .y = radius};

bool is_in_circle(Point point) {
    return sq_distance(point, center) < sqr(radius);
}

struct Point generate() {
    struct Point p;  // = {};
    // {.x = random(), .y = random()}
    p.x = random();
    p.y = random();
    return p;
}

volatile int flag = 0;

void handler(int) {
    flag = 1;
}


// 3 sec total

int main() {
    // srandom(time(NULL));
    srandom(42);

    // struct itimerval tm_ = {};
    // tm_.it_interval.tv_sec = 0;
    // tm_.it_interval.tv_usec = 0;
    // tm_.it_value.tv_sec = 2;
    // tm_.it_value.tv_usec = 1000000 - 20000; // -20ms
    // setitimer(ITIMER_REAL, &tm_, NULL);
    // signal(SIGALRM, &handler);

    int tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    const struct itimerspec itmspec = {.it_interval = 0, .it_value = {.tv_sec = 2, .tv_nsec = 1000000000 - 20000000} };
    printf("%d\n", tfd);
    printf("%d\n", timerfd_settime(tfd, 0, &itmspec, NULL));
    size_t overall = 0, in_circ = 0;
    uint64_t val;
    while (read(tfd, &val, sizeof(val)) == -1) {
        in_circ += is_in_circle(generate());
        ++overall;
    }
    printf("%lf\n", (double)(in_circ)/overall * 4);
    printf("%zu\n", overall);
    close(tfd);
}
