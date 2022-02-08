#include <inttypes.h>
#include <stdio.h>
#include <math.h>

struct Struct {
    int x;
    short y;
};

union Union {
    int x;
    short y;
};

struct StructBitFloat {
    unsigned m: 23;
    unsigned e: 8;
    unsigned s: 1;
};

union BitFloatCast {
    struct StructBitFloat bits;
    float f;
};

struct Struct s;


struct Struct2 {
    short x;
    short y;
    short z;
};

int main() {
    sizeof(float) == sizeof(int) == sizeof(unsigned);
    sizeof(double) == 64 == sizeof(long long) == sizeof(int64_t);
    printf("%zu\n", sizeof(long double));

    float f;
    scanf("%f", &f);
//    printf("%.10f\n", f);
//
//    printf("%.10f\n", f/0);
//    float inf = f/0;
//    printf("%.10f\n", -((-inf)*0.0f));
//
//    float x = 1e10f;  // 1u <<
//
//    isinf(x);
//    isnan(x);

    printf("%u\n", ((*(unsigned*)&f)) >> 31u);
    printf("%u\n", (((*(unsigned*)&f)) >> 23u) & 255u);
    printf("%x\n", (((*(unsigned*)&f)) >> 0u) & ((1u << 23u) - 1));

    union BitFloatCast bc;
    bc.f = f;
    printf("%u\n", bc.bits.s);
    printf("%u\n", bc.bits.e);
    printf("%x\n", bc.bits.m);
}


