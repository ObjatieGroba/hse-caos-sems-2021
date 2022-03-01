#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

int main() {
    printf("abcd");
    fflush(stdout);
    int fd = open("a.txt", O_RDWR | O_CREAT, 0600);
    char * c = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (!fork()) {
        /// Child
        for (int i =0; i != 3; ++i) {
            sleep(1);
            printf("%d\n", getppid());
        }
        c[1000] = 'a';
        return -1;
    }
    /// Parent
    printf("%d\n", getppid());
    printf("%d\n", getpid());
    int st;
    wait(&st);
    if (WIFEXITED(st)) {
        printf("%d\n", WEXITSTATUS(st));
    }
    if (WIFSIGNALED(st)) {
        printf("s %d\n", WSTOPSIG(st));
    }
    wait(&st);
    printf("%c\n", c[1000]);
}
