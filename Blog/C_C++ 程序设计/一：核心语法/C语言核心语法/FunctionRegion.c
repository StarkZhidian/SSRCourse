#include <stdio.h>

void fun() {
    // 该变量仅在该函数内部有效
    int functionRegionVar;
    printf("functionRegionVar = %d\n", functionRegionVar);
}

int main() {
    fun();
    // error: ‘functionRegionVar’ undeclared 
    // functionRegionVar = 2;
    return 0;
}