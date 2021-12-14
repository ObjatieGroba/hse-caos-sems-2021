#include <stdlib.h>
#include <stdio.h>

int gg = 10;

int gen() {
    --gg;
    return gg;
}

int main() {
    int x;
    int size = 0;
    int capacity = 0;
    int *vec = NULL;
    while ((x = gen()) != 0) {
        if (size == capacity) {
            capacity += 1;
            capacity *= 2;
            int *res = realloc(vec, capacity);
            if (!res) {
                free(vec);
                return 1;
            }
            vec = res;
        }
        vec[size++] = x;
    }
    free(vec);
}
