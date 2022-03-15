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
/// (CMD1; CMD2)

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }
    int pid = fork();
    if (pid == 0) {
        int pid1 = fork();
        if (pid1 == 0) {
            execlp("bash", "bash", "-c", argv[1], NULL);
            _exit(1);
        }
        int status;
        wait(&status);
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            exit(1);
        }
        pid1 = fork();
        if (pid1 == 0) {
            execlp("bash", "bash", "-c", argv[2], NULL);
            _exit(1);
        }
        wait(NULL);
    }
    wait(NULL);
    return 0;
}

