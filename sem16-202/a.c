/// CMD1 | CMD2

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


int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    int fd_pipe[2];
    pipe(fd_pipe);

    int pid1 = fork();
    if (pid1 == 0) {
        dup2(fd_pipe[1], 1);
        // close(fd_pipe[0]);
        // close(fd_pipe[1]);
        // execlp(argv[1], argv[1], NULL);
        execlp("bash", "bash", "-c", argv[1], NULL);
        _exit(1);
    }
    close(fd_pipe[1]);
    int pid2 = fork();
    if (pid2 == 0) {
        dup2(fd_pipe[0], 0);
        close(fd_pipe[0]);
        // execlp(argv[2], argv[2], NULL);
        execlp("bash", "bash", "-c", argv[2], NULL);
        _exit(1);
    }
    close(fd_pipe[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}
