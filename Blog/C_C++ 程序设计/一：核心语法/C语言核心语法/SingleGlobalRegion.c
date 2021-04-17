#include<stdio.h>

/* 单文件全局作用域变量，默认值为 0 */
int singleGlobalVar;

void fun() {
    singleGlobalVar = 1;
}

int main() {
    fun();
    printf("singleGlobalVar = %d\n", singleGlobalVar);
    return 0;
}