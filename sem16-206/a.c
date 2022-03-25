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
    // PANIC_IF(argc != 2, "invalid number of arguments: pass only command to execute");
    // execlp("bash", "bash kek", -c", argv[1], NULL);

    time_t timep;
    time(&timep);
    // time_t polgoda = 60*60*24*365/2;
    // timep -= polgoda;
    // Високосные плачуть
    struct tm *cur_time = localtime(&timep);
    printf("%d %d %d %02d:%02d:%02d\n", cur_time->tm_mday, cur_time->tm_mon + 1, cur_time->tm_year + 1900, cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);

    if (cur_time->tm_mon < 6) {
        cur_time->tm_mon += 12;
        // assume we are living not in 1900
        --cur_time->tm_year;
    }
    cur_time->tm_mon -= 6;
    cur_time->tm_isdst = -1;
    mktime(cur_time);
    printf("%d %d %d %02d:%02d:%02d\n", cur_time->tm_mday, cur_time->tm_mon + 1, cur_time->tm_year + 1900, cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
    timep += 100500;
    localtime(&timep);
}
