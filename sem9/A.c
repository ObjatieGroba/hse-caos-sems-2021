float diag(float x, float y, float z);

double func(double *a, double *b, int n) {  //  n % 2 == 0
    double result = 0;
    for (int i = 0; i < n; i += 2, a += 2, b += 2) {
        asm (
        "movupd (%[a]), %%xmm0\n\t"
        "movupd (%[b]), %%xmm1\n\t"
        "mulpd %%xmm0, %%xmm1\n\t"
        "movss (%[result_ptr]), %%xmm0\n\t"
        "haddpd %%xmm0, %%xmm1\n\t"
        "movss %%xmm0, (%[result_ptr])\n\t"
        :
        : [a] "r" (a),
          [b] "r" (b),
          [result_ptr] "r" (&result)
        : "memory" );
    }
    return result;
}

#include <stdio.h>

int main() {
    printf("%f\n", diag(1, 2, 3));
    double a[2] = {1., 2.};
    double b[2] = {3., 4.};
    printf("%f\n", func(a, b, 2));
}
