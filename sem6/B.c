// |Arg  |sin  |exp  |
// |  0.0|  0.0|  0.0|

// ./a.out 100

#include <math.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    int width;
    if (sscanf(argv[1], "%d", &width) != 1) {
        fprintf(stderr, "Error occured in scanf!" "", __LINE__);
        return 1;
    }


    // char buf[100500];
    // sprintf(buf, "%%%dd", width); // width == 10 -> %10d

    float x;
    if (scanf("%f", &x) != 1) {
        fprintf(stderr, "Error occured in scanf!" "", __LINE__);
        return 1;
    }

    if (printf("|%-*s|%-*s|%-*s|\n", width, "Arg", width, "sin", width, "exp") != 3) {
        return 1;
    }

    if (printf("|%*.1f|%*.1f|%*.1f\n", width, x, width, sin(x), width, exp(x))) {
        return 1; // exit(1);
    }
    fflush(stdout);
    return 0;
}
