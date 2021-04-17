#include <stdio.h>

/**
 * 打印出浮点数 f 在内存中的二进制编码数据 
 */
void showFloatBits(double f) {
	int *fp = (int *) &f;
	int *fpNext = fp++;
	int size = sizeof(int) * 8;
	int i;
	// 打印前 4 字节数据 
	for (i = 0; i < size; i++) {
		printf("%d", ((*fp) >> (size - 1 - i)) & 1);
	}
	// 打印后 4 字节数据 
	for (i = 0; i < size; i++) {
		printf("%d", ((*fpNext) >> (size - 1 - i)) & 1);
	}
	printf("\n");
} 

int main() {
	double c = 0.1;
	showFloatBits(c); 
	return 0;
} 
