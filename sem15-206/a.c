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


/// ./a.out ls
/// main(2, [./a.out, ls])


#define PANIC_IF(cond, ...) \
  do {  \
  	if (cond) { \
    	fprintf(stderr, __VA_ARGS__); \
    	exit(1); \
      }} while(0)

int main(int argc, char** argv) {
    PANIC_IF(argc != 2, "Error: invalid number of arguments\n");

    pid_t pid = fork();
    PANIC_IF(pid < 0, "Error: can't fork\n");
    if (pid == 0) {
        // PANIC_IF(execv(argv[0]), "")

        execlp(argv[1], argv[1], NULL);
        return 1;
    } else {
        int wstatus;
        wait(&wstatus);
        printf("%d\n", WEXITSTATUS(wstatus));
    }
}