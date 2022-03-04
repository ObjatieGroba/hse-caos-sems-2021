// ./a.out filename cols rows 

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

int main(int argc, char **argv) {
    // int table[cols][rows];
    if (argc < 4) {
        puts("no args");
        exit(1);
    }
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);  // 0600
    if (fd < 0) {
        puts("can not create file");
        exit(2);
    }

    // size_t cols = atoul(argv[2]); // Плохо - игнорируем ошибку

    // long int strtol(const char *nptr, char **endptr, int base);
    const char *ptr;
    size_t cols = strtol(argv[2], &ptr, 10);
    if (!ptr || *ptr) {
        puts("Not a number");
        close(fd);  // лучше было до открытия файла сделать эти чтения чисел
        exit(3);
    }

    size_t rows = 0;
    if (sscanf(argv[3], "%zu", &rows) < 1) {
        puts("Not a number");
        close(fd);  // лучше было до открытия файла сделать эти чтения чисел
        return 4;
    }


    int * table;
    const size_t table_size_bytes = sizeof(*table) * rows * cols;
    table = mmap(
            NULL,
            table_size_bytes,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            fd,
            0
    );
    if (table == MAP_FAILED) {
        puts("Failed to read");
        close(fd);
        exit(5);
    }

    if (ftruncate(fd, table_size_bytes) == -1) {
        puts("Truncate failed");
        close(fd);
        exit(6);
    }
    pid_t some_pid;
    if ((some_pid = fork()) == 0) {
        // Child
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (i % 2) {
                    table[i * cols + j] = 1;
                }
            }
        }
        if (munmap(table, table_size_bytes) == -1) {
            puts("unmap error");
            close(fd);
            return 1;
        }
        close(fd);
        return 0;
    } else if (some_pid == -1) {
        puts("fork error");
        ftruncate(fd, 0);
        munmap(table, table_size_bytes);
        close(fd);
        return 7;
    }
    // Parent
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (i % 2 == 0) {
                table[i * cols + j] = 2;
            }
        }
    }
    int wstatus;
    wait(&wstatus);
    if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0) {
        puts("child error");
        ftruncate(fd, 0);
        close(fd);
        return 8;
    }
    if (munmap(table, table_size_bytes) == -1) {
        puts("unmap error");
        ftruncate(fd, 0);
        close(fd);
        return 8;
    }
    close(fd);
    return 0;
}
