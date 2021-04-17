#include <stdio.h>

/**
 * ��ӡ�������� f ���ڴ��еĶ����Ʊ������� 
 */
void showFloatBits(double f) {
	int *fp = (int *) &f;
	int *fpNext = fp++;
	int size = sizeof(int) * 8;
	int i;
	// ��ӡǰ 4 �ֽ����� 
	for (i = 0; i < size; i++) {
		printf("%d", ((*fp) >> (size - 1 - i)) & 1);
	}
	// ��ӡ�� 4 �ֽ����� 
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
