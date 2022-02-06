#include <stdio.h>

double mul(double x[2], double y[2]) {  /// return x[0] * y[0] + x[1] * y[1]
    double ans;
    __asm__ (
    "movupd (%[x]), %%xmm0\n\t"
    "movupd (%[y]), %%xmm1\n\t"
    "mulpd %%xmm0, %%xmm1\n\t"
    "haddpd %%xmm1, %%xmm1\n\t" // а поч горизонтальные? --- потому что нужна сумма произведений внутри одного регистра?)
    "movsd %%xmm1, %0"
    : "=m"(ans)
    : [x]"r"(x), [y]"r"(y)
    : "xmm0", "xmm1"
    );
    return ans;
}

int main() {
    double x[2] = {1., 2.};
    double y[2] = {2., 3.};
    printf("%lf\n", mul(x, y));
}

