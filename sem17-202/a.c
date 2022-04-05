#include <signal.h>
#include <stdio.h>

int x;

void handler(int sig) {
//    signal(sig, handler);  - нам не надо
//    printf("We got sig\n"); - НИКОГДА!
    x = x + 1;  /// int y = x; y += 1; x = y;

}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0 | SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);

    while (1) {
        char c;
        scanf("%c", &c);
        x = x + 1;  /// x += 1
    }
}
