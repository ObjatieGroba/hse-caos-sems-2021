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
#include "time.h"


#define PANIC_IF(cond, ...) \
  do {  \
  	if (cond) { \
    	fprintf(stderr, __VA_ARGS__); \
    	exit(1); \
    } \
  } while(0)

int main(int argc, const char** argv) {
    PANIC_IF(argc != 2, "invalid number of arguments: pass only command to execute");
    volatile double start_time_point = time(NULL); // clock();
    if (!fork()) {
        execlp("bash", "bash kek", "-c", argv[1], NULL);
    } else {
        wait(NULL);
        printf("%lf\n", ((double) time(NULL) - start_time_point));
    }
}
