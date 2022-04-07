/// SIGUSR1 -> printf("catch")

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


// volatile int x;
volatile int is_signaled = 0;

void catch_sigusr1(int) {
    // printf("Catched SIGUSR1\n"); -- нельзя, можно заблокироваться на write(stdout, buf, size)
    // malloc(); -- нельзя
    // x = x + 1;
    is_signaled += 1;
}

int main() {
    printf("%d\n", getpid());
    // signal(SIGUSR1, &catch_sigusr1);
    struct sigaction sa = {};

    sa.sa_flags = SA_RESTART;
    sa.sa_handler = catch_sigusr1;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);

    while (1) {
        // char c;
        // scanf("%c", &c);
        // x += 1; // inc %reg
        // x = x + 1;  // int t = x;  /HERE/   t += 1; x = t;

        while (is_signaled) {
            printf("Catched SIGUSR1\n");
            is_signaled -= 1;
        }
    }
}
