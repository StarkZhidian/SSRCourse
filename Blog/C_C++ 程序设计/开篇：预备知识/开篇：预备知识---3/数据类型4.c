#include <stdio.h>

int main() {
    // 0b 开头的代表这是一个二进制编码数据
	int c = 0b01000001;
	float *cp = (float *)&c;
	// %.128f 表示输出一个浮点数，结果保留 128 位小数
	printf("%.128f\n", *cp);
	return 0;
} 
