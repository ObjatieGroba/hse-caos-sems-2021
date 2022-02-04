// ./a.out myfile.txt
// This is file
// sys.argv

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    const char* path = argv[1];
    struct stat st;
    if (lstat(path, &st)) {
        return 1;
    }

    if (S_ISREG(st.st_mode)) {
        printf("Regular file with size %lu\n", st.st_size);
    }
    if (S_ISDIR(st.st_mode)) {
        printf("Directory with header size %lu\n", st.st_size);
    }

}
