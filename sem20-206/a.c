// ./a.out localhost 1234 3
// connect to tcp://localost:1234 for 3 secs

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <netdb.h>

#define PANIC_IF(zxc, ...) do {if (zxc) {fprintf(stderr, __VA_ARGS__); exit(1); } } while(0)

int create_timer(int secs) {
    int tfd = timerfd_create(CLOCK_REALTIME, 0);
    const struct itimerspec itmspec = {.it_interval = 0, .it_value = {.tv_sec = secs, .tv_nsec = 0} };
    timerfd_settime(tfd, 0, &itmspec, NULL);
    return tfd;
}

int main(int argc, char **argv) {
    int secs = atoi(argv[3]);


    const char* host = argv[1];
    const char* port = argv[2];
    struct addrinfo hints = {};
    struct addrinfo* res;
    PANIC_IF(getaddrinfo(host, port, &hints, &res), "getaddrinfo failed");

    int socket_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    int connect_res = connect(socket_fd, res->ai_addr, res->ai_addrlen);

    int epollfd = epoll_create1(0);
    struct epoll_event evt = {};
    evt.data.fd = socket_fd;
    evt.events = EPOLLOUT;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, socket_fd, &evt);
    int timer_fd = create_timer(secs);
    evt.data.fd = timer_fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, timer_fd, &evt);

    PANIC_IF(epoll_wait(epollfd, &evt, 1, -1) != 1, "Epoll wait failure");
    PANIC_IF(evt.data.fd == timer_fd, "Timeout");

    printf("%zd\n", write(socket_fd, "abcd", 4));

    // int epollfd = epoll_create;
}
