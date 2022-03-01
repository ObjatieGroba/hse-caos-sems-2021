#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

int main() {
    int fd = open("a.txt", O_RDWR | O_CREAT, 0600);
    char * c = mmap(NULL, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (c == MAP_FAILED) {
        printf("error\n");
        return 1;
    }
    ftruncate(fd, 500);
    c[1999] = 'a';
    printf("%c\n", c[1999]);
    ftruncate(fd, 2000);
    munmap(c, 1000);
}
