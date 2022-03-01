#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define DO_PRE_TRASH() ftruncate(fd, 0); close(fd);
#define DO_TRASH() munmap(buf, file_size); DO_PRE_TRASH();
#define NO_TRASH() munmap(buf, file_size); close(fd);

#define forever for (;;)

int main(int argc, char **argv) {
//    forever {
//    }
    if (argc < 4) {
        return 1;
    }
    const char *filename = argv[1];
    int rows, cols;
    if (sscanf(argv[2], "%d", &rows) != 1 || sscanf(argv[3], "%d", &cols) != 1) {
        return 2;
    }
    // int rows = atol(argv[2]), cols = strtol(argv[3], char**);
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        return 3;
    }
    size_t file_size = rows * cols * sizeof(int);
    ftruncate(fd, file_size);
    int* buf = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        DO_PRE_TRASH();
        return 4;
    }
    int pid = fork();
    if (pid == -1) {
        DO_TRASH();
        return 1;
    } else if (pid == 0) {
        // child
        for (int row = 0; row < rows; rows += 2) {
            for (int col = 0; col < cols; ++col) {
                buf[row * cols + col] = 1;
            }
        }
        NO_TRASH();
        return 0;
    }
    // parent
    for (int row = 1; row < rows; rows += 2) {
        for (int col = 0; col < cols; ++col) {
            buf[row * cols + col] = 2;
        }
    }
    int status;
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        DO_TRASH();
        return 1;
    }
    NO_TRASH();
    return 0;
}

