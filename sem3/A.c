#include <stdio.h>

int nth_elem(int a, int b, unsigned n);

int main() {
    int a, b;
    unsigned n;
    printf("%d\n", scanf("%d%du", &a, &b, &n));
//    a = 0x40000000;
//    b = 0x80000000;
//    n = 3;
    printf("%d\n", nth_elem(a, b, n));
    printf("0x%x\n", nth_elem(a, b, n));
}
