#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * replace(char * s, char from, char to) {
    if (s == NULL) {
        return NULL;
    }
//    size_t ind = 0;
//    s[ind]; - Это операция индексирования
    char *ans = s;         // Сохраняю начало строки
    while (*s != '\0') {
        if (*s == from) {
            *s = to;
        }
        ++s;
    }
    return ans;
}

int main() {
//    printf("%s\n", NULL);
    char a[] = "abcdef";
//    char * a = malloc(13);
//    strcpy(a, "abcdefg"); /// strncpy

    replace(a, 'b', 'z');
    printf("%s\n", a);

//    free(a);

    return 0;
}
