// ./a.out myfile.txt
// This is file
// sys.argv

// realpath(const char *restrict file_name, char *restrict resolved_name); – returns the canonicalized absolute pathname


#include <stdio.h>
#include <error.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    char buf_[PATH_MAX];
    errno = 0;
    char *buf = realpath(argv[0], buf_);
    if (buf == NULL) {
        printf("Error: %d", errno);
    }

    char* end = buf + strlen(buf) - 1;
    while (*end != '/') {
        --end;
    }
    if (end == buf) {
        printf("/\n");
        return 0;
    }
    char* end1 = end - 1;
    while (*end1 != '/') {
        --end1;
    }
    *end = '\0';
    printf("%s\n", end1 + 1);
}
