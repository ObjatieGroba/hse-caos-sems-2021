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

int main() {
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // host to network of integer size of long  - 0.0.0.0
    serv_addr.sin_port = htons(8000);  // host to network of integer size of short

    bind(listen_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listen_sock, 2);
    char buf[4096];
    while (1) {
        int client_sock = accept(listen_sock, (struct sockaddr *) NULL, NULL);
        if (fork() == 0) {
            close(listen_sock);
            printf("Accepted %d\n", client_sock);
            ssize_t r;
            while ((r = read(client_sock, buf, sizeof(buf))) > 0) {
                write(client_sock, buf, r);
            }
            close(client_sock);
            exit(0);
        } else {
            close(client_sock);
        }
    }

    close(listen_sock);
}