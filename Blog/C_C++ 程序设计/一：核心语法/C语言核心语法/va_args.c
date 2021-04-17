#include <stdio.h>
#define PR(...) printf(__VA_ARGS__)

int main() {
    int x = 1;
    float y = 2.1f;
    PR("x = %d, y = %f\n", x, y);
    return 0;
}