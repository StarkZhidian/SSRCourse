#include <stdio.h>

int main() {
    // 0b 开头的代表这是一个二进制编码数据
	long long c = 0b01000001;
	double *dp = (double *) &c;
	printf("%.1024lf\n", dp); 
	return 0;
} 
