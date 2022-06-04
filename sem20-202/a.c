/// ./a.out localhost 7777 3  -> Connect to 127.0.0.1 7777 with timeout 3 seconds

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/timerfd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <stdlib.h>

enum {
    OK = 0,
    TIMEOUT = 1,

    MAX_EVENTS = 10,
};

void callback(int fd, int status) {
    printf("Callback %d\n", status);
}

void async_read(int fd, int timeout_secs) {
    struct itimerspec new_val = {
            .it_value = {
                    .tv_sec = timeout_secs,
                    .tv_nsec = 0
            }
    };
    int tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
    timerfd_settime(tfd, 0, &new_val, NULL);
    ///
    int epollfd = epoll_create1(0);
    struct epoll_event ev, events[MAX_EVENTS];
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
        perror("epoll_ctl: fd");
        exit(EXIT_FAILURE);
    }
    ev.data.fd = tfd;
    ev.events = EPOLLIN;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, tfd, &ev) == -1) {
        perror("epoll_ctl: tfd");
        exit(EXIT_FAILURE);
    }
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }
    for (int n = 0; n < nfds; ++n) {
        if (events[n].data.fd == fd) {
            callback(fd, OK);
            break;
        } else {
            callback(fd, TIMEOUT);
            break;
        }
    }
}

int main(int argc, char ** argv) {
    if (argc <= 2) {
        printf("Usage: %s host port timeout\n", argv[0]);
        return 1;
    }

    struct addrinfo hints = {};
    struct addrinfo* addr_info = NULL;
    if (getaddrinfo(argv[1], argv[2],
                    &hints, &addr_info) != 0) {
        return 1;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (connect(sockfd,
                addr_info->ai_addr,
                addr_info->ai_addrlen) != 0) {
//        return 1;
    }

    // freeaddrinfo
    // close

    // dup2(sockfd, 0);
    // dup2(sockfd, 1);
    write(sockfd, "ping", 4);
    async_read(sockfd, 3);
}
