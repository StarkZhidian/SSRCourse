#include <stdio.h>

int main() {
    // 0b ��ͷ�Ĵ�������һ�������Ʊ�������
	long long c = 0b01000001;
	double *dp = (double *) &c;
	printf("%.1024lf\n", dp); 
	return 0;
} 
