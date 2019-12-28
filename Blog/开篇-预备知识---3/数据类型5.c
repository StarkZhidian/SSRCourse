#include <stdio.h>

/**
 * 打印出浮点数 f 在内存中的二进制编码数据 
 */
void showFloatBits(float f) {
	int *fp = (int *) &f;
	int size = sizeof(f) * 8;
	int i;
	for (i = 0; i < size; i++) {
		printf("%d", (*fp) >> (size - 1 - i) & 1);
	}
	printf("\n");
} 

int main() {
    // 0b 开头的代表这是一个二进制编码数据
	float c = 0b01000001;
	showFloatBits(c); 
	return 0;
} 