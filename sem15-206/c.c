#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "inttypes.h"
#include "sys/mman.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"


/// ./a.out ls ls2 cat
/// (ls; ls2) | cat


#define PANIC_IF(cond, ...) \
  do {  \
  	if (cond) { \
    	fprintf(stderr, __VA_ARGS__); \
    	exit(1); \
      }} while(0)

int main(int argc, char** argv) {
    PANIC_IF(argc != 4, "Error: invalid number of arguments\n");

    int fds[2];
    if (pipe(fds) < 0) {
        return 1;
    }

    pid_t pid = fork();
    PANIC_IF(pid < 0, "Error: can't fork\n");
    if (pid == 0) {

        dup2(fds[1], 1);
        pid_t pid2 = fork();
        PANIC_IF(pid2 < 0, "Error: can't fork\n");

        if (pid2 == 0) {
            execlp(argv[1], argv[1], NULL);
            return 1;
        }

        wait(NULL);
        execlp(argv[2], argv[2], NULL);
        return 1;
    }

    close(fds[1]);

    // int wstatus;
    // wait(&wstatus);
    pid_t pid2 = fork();
    PANIC_IF(pid2 < 0, "Error: can't fork\n");
    if (pid2 == 0) {
        dup2(fds[0], 0);
        execlp(argv[3], argv[3], NULL);
        return 1;
    }
    int g_status;
    wait(NULL);
    wait(NULL);
    return 0;
}
