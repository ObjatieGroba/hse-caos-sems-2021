#include <setjmp.h>
#include <stdio.h>

jmp_buf env;

void f(int *x) {
    printf("f %d\n", *x);
    *x = 2;
    longjmp(env, 6);
}

void g(int *x) {
    printf("g %d\n", *x);
    *x = 1;
    setjmp(env);
}

int main() {
    int x = 0;
    g(&x);
    f(&x);
}
