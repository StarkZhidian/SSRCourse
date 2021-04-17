#include <stdio.h>
// 这里因为 custom2.h 已经 #include "custom1.h" 了，所以这里直接包含 custom2.h 即可
#include "custom2.h"

int main() {
    int maxValue = maxx(1, 2, 3);
    int minValue = minn(1, 2, 3);
    printf("max value = %d\n", maxValue);
    printf("min value = %d\n", minValue);
    return 0;
}