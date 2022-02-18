/// mymalloc(size_t n) -> int *
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int *mymalloc_old(size_t n) {
    return (int*) calloc(n, sizeof(int));  // free(prt);
}

int *mymalloc_new(size_t n) {
    return (int*) mmap(
            NULL,
            sizeof(int) * n,
            PROT_READ | PROT_WRITE,
            MAP_ANONYMOUS | MAP_PRIVATE,     // MAP_PRIVATE ???
            -1, //fd,
            0);
}

int main() {
    errno = 0;
    int * x = mymalloc_new(1);
    if (x == MAP_FAILED) {  /// x != (int*) -1
        fprintf(stderr, "FAILED %d\n", errno);
        return 1;
    }
    x[8] = 5;
    printf("%d\n", x[8]);
}
