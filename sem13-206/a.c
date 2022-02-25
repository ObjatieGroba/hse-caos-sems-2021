#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main() {
    printf("hello");
    fflush(stdout);
    pid_t tmp;
    int *arr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    *arr = 2;
    if ((tmp = fork()) == 0) {
        // Child
        *arr = 42;
        sleep(2);
        printf("curr_pid: %d\n", getpid());
        munmap(arr, sizeof(int));
        return 0;
    }
    //  Parent
    printf("parent_pid: %d\n", getpid());
    printf("value in arr: %d\n", *arr);
    int wstatus;
    wait(&wstatus);
    printf("value in arr: %d\n", *arr);
    if (WIFEXITED(wstatus)) {
        printf("exited normally %d\n", WEXITSTATUS(wstatus));
    } else if (WIFSIGNALED(wstatus)) {
        printf("killed with sygnal %d\n", WTERMSIG(wstatus));
    }
    munmap(arr, sizeof(int));
    return 0;
}
