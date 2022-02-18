// Посчитать колчиество пробельных символов в файле по пути filename

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/file.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>


size_t count_spaces(const char* filename) {
    static_assert(0600 != 600, "hmm");
    int fd = open(filename, O_RDWR | O_CREAT, 0600); // не уверен что флаг такой
    if (fd < 0) {
        printf("Failed to open file");
        return ULONG_MAX;
    }

    struct stat stat_result;
    fstat(fd, &stat_result);
//    size_t size = stat_result.st_size;
    char* zz = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ftruncate(fd, 1000);
    if (zz == MAP_FAILED || zz == NULL) {
        printf("Failed to map file");
        return ULONG_MAX;
    }
    size_t spaces = 0;
    const char * end = zz + 1000;
    for (const char* iter = zz; iter != end; ++iter) {
        spaces += !!isspace(*iter);
    }
    ++zz[0];
    zz[888] = 'x';
    close(fd);
    munmap(zz, 1000);
    return spaces;
}

int main(int argc, char**argv) {
    printf("%ld\n", count_spaces(argv[1]));
}
