#include <stdio.h>
#include <stdlib.h>

int f();
//const char * str = "asdfaaa";
const char * str = NULL;

int main() {
    if (scanf("%ms", &str) != 1) {
//        printf("%s", "Empty\n");
        printf("Empty\n");
        return 0;
    }
    int r = f();
    free((void*)str);
    printf("%d\n", r);
}
