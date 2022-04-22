#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <time.h>

#define MAX_EVENTS 10

//struct Public {
//    int ip;
//    char pad[100500];
//};
//
//struct Private {
//    int ip;
//    int x;
//    int y;
//};


void do_use_fd(int client_fd) {
    char buf[4096];
    ssize_t r = read(client_fd, buf, sizeof(buf));
    if (r != 0) {
        write(client_fd, buf, r);
    }
}

#define MAX_CLIENTS 3

int main() {
    int listen_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    if (listen_sock == -1) {
        exit(1);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // host to network of integer size of long  - 0.0.0.0
    serv_addr.sin_port = htons(8000);  // host to network of integer size of short

    bind(listen_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listen_sock, 2);

    char buf[4096];
    int client_sockets[MAX_CLIENTS] = {};
    for (size_t i = 0; i < MAX_CLIENTS; ++i) {
        client_sockets[i] = -1;
    }
    while (1) {
        {
            int client_sock = accept(listen_sock, (struct sockaddr *) NULL, NULL);
            if (client_sock != -1) {
                printf("Accepted %d %d\n", client_sock,
                       fcntl(client_sock, F_SETFL, fcntl(client_sock, F_GETFL, 0) | O_NONBLOCK));
                for (size_t i = 0; i < MAX_CLIENTS; ++i) {
                    if (client_sockets[i] == -1) {
                        client_sockets[i] = client_sock;
                        break;
                    }
                    if (i == MAX_CLIENTS - 1) {
                        close(client_sock);
                    }
                }
            }
        }
        for (size_t i = 0; i < MAX_CLIENTS; ++i) {
            int client_sock = client_sockets[i];
            if (client_sock == -1) {
                continue;
            }
            ssize_t r;
            errno = 0;
            if ((r = read(client_sock, buf, sizeof(buf))) > 0) {
                write(client_sock, buf, r);
            }
            if (r == -1 && errno != EAGAIN) {
                close(client_sock);
                printf("Closed %d\n", client_sock);
                client_sockets[i] = -1;
            }
        }
    }
}