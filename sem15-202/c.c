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

/// ./a.out "ls -la" "echo aaaa"
/// (CMD1 | CMD2)

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    int pid = 0; // fork();
    if (pid == 0) {
        int pid1 = fork();
        int fd_pipe[2];
        pipe(fd_pipe);

        if (pid1 == 0) {
            close(fd_pipe[0]);
            dup2(fd_pipe[1], 1);
            close(fd_pipe[1]);

            execlp("bash", "bash", "-c", argv[1], NULL);
            _exit(1);
        }
        close(fd_pipe[1]);
        int pid2 = fork();
        if (pid2 == 0) {
            dup2(fd_pipe[0], 0);
            close(fd_pipe[0]);
            execlp("bash", "bash", "-c", argv[2], NULL);
            _exit(1);
        }
        wait(NULL);
        wait(NULL);
    }
    wait(NULL);
    return 0;
}
