#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int flag = 0;

void handler(int sig) {
    flag = 1;
}

int main() {
    printf("%d\n", getpid());

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0 | SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    while (1) {
        if (flag) {
            printf("We got signal\n");
            flag = 0;
        }
    }
}
