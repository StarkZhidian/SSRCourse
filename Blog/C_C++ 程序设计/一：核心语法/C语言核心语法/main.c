#include <stdio.h>

// 这里进行了函数的声明，该声明等价于：extern void fun();
// 这个函数定义在 GlobalVarable.c 中。
void fun();

int main() {
    // 这里使用了 extern 关键字声明该变量可能在其他源文件中定义
    // extern int externGlobalVar;
    // printf("externGlobalVar = %d\n", externGlobalVar);
    fun();
    return 0;
}