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

//int main(int argc, char **argv, char **envp)
//{
//    for (char **env = envp; *env != 0; env++)
//    {
//        char *thisEnv = *env;
//        printf("%s\n", thisEnv);
//    }
//    return 0;
//}

/// ./cmd < input.txt
/// ./a.out ./cmd input.txt

int main(int argc, char **argv) {
    if (argc != 3) {
        return 1;
    }

    int fd = open(argv[2], O_RDONLY);

    // int fd_copy = dup(fd);
    // dup3(fd, 0);

    dup2(fd, 0);
    close(fd);
    // execlp(argv[1], argv[1], NULL);
    execlp("bash", "bash ne nash", "-c", argv[1], NULL);
    // _exit(1); -- маст хев
    return 2;  /// Если здесь, то точно ошибка
}

