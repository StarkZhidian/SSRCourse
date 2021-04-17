#include <stdio.h>

inline __attribute__((always_inline)) int fun() {
    return 1;
}

int main() {
    int x = fun();
    printf("x = %d\n", x);
    return 0;
}