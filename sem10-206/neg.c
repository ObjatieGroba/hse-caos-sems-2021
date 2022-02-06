#include <asm/unistd_32.h>
#include <unistd.h>

ssize_t read(int fd, char *buf, size_t n) {

    ssize_t ans;
    __asm__ (
    // "mov $__NR_read, %%eax\n\t"
    // "mov %1, %%ebx\n\t"
    // "mov %2, %%ecx\n\t"
    // "mov %3, %%edx\n\t"
    "int $0x80\n\t"
    "mov %%eax, %0"
    : "=rm"(ans)
    : "a" (SYS_read), "b"(fd), "c"(buf), "d"(n)
    : "memory", "eax" // , "ebx", "ecx", "edx"
    );
    return ans;
}
