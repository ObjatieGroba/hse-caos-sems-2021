#include "math.h"

double pow222(double a, double b) {
    return pow(a, b);
}

double mypow(double a, double b) {
    asm volatile (
    "movsd (%[a]), %%xmm1 \n\t"
    "movsd (%[b]), %%xmm2 \n\t"
    "comisd %%xmm1, %%xmm2 \n\t"
    "jge no_swap \n\t" 			   // если >= скипаем своп
    "movsd (%[a]), %%xmm3 \n\t"
    "movsd (%[b]), %%xmm4 \n\t"
    "movsd %%xmm4, (%[a]) \n\t"
    "movsd %%xmm3, (%[b]) \n\t"
    "no_swap: \n\t"
    "push %[pow222]\n\t"
    "ret \n\t"
    : [a] "+g" (a), [b] "+g" (b)  // output
    : [pow222] "r" (&pow222)														// input
    : "xmm1", "xmm2", "xmm3"			// clobbers
    );
}

int main() {
    mypow(1, 2);
}
