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
#include "time.h"


int main() {
    time_t current_time = time(NULL);
    struct tm* b_time = localtime(&current_time);

    // localtime(current_time + 100500);

    printf("%d:%d:%d %d-%d-%d\n",
           b_time->tm_hour,
           b_time->tm_min,
           b_time->tm_sec,
           b_time->tm_mday,
           1+b_time->tm_mon,
           1900+b_time->tm_year);

    b_time->tm_mday += 100500;
    b_time->tm_isdst = -1;  // Иначе не учтем правльно зимнее время
    printf("%ld\n", mktime(b_time));
}