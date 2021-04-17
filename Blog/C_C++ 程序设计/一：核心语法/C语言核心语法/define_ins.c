#include <stdio.h>
#define PR printf
// 这里的宏定义值中，通过 ##x 获取宏调用时传入的实际参数名
#define XNAME(n) x ##n

int main() {
    int xy = 1;
    int x2 = 2;
    PR("xy = %d\n", XNAME(y));
    PR("x2 = %d\n", XNAME(2));
    return 0;
}