#include <stdio.h>
#include <setjmp.h>
#include <stdnoreturn.h>

jmp_buf my_jump_buffer;

void foo(int count) {
    // int x; /// BAN
    // int * x_register = malloc(sizeof(int));
    // del x; /// OK

    printf("foo(%d) %d called\n", count, setjmp(my_jump_buffer));
    /// push setjmp()
    /// push count
    /// push "foo..."
    /// call printf

    /// subl $12, esp
    /// mov 0(esp), "foo..."
    /// mov 4(esp), count
    /// mov 8(esp), setjmp()
    /// call printf
}

void doo(int x) {
    printf("abcde %d %d\n", 100, 500);
    longjmp(my_jump_buffer, 2);
}

int main(void) {
    foo(1);
    doo(10);
}
