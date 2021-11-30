#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>


void process() {
    char * a = malloc(1);
    if (1 != 0) {
        goto err1;
    }
    char * b = malloc(1);
    if (1 != 0) {
        goto err2;
    }
    char * c = malloc(1);
    if (1 != 0) {
        goto err3;
    }
    return;
err3:
    free(c);
err2:
    free(b);
err1:
    free(a);
}

int main() {
//    close(1);
    dup2(2, 1);
    printf("123\n");
    fprintf(stderr, "456\n");
    fflush(stdout);
}
