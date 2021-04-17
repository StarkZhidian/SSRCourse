#include <stdio.h>

void fun() {

    {
        // 块级作用域变量，只在当前块级可见
        int blockRegionVar = 1;
        printf("blockRegionVar = %d\n", blockRegionVar);
    }
    // error: ‘blockRegionVar’ undeclared
    // blockRegionVar = 2;
}

int main() {
    fun();
    return 0;
}