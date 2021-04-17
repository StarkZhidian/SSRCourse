#include <stdio.h>

/**
 * ��ӡ�������� f ���ڴ��еĶ����Ʊ������� 
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
    // 0b ��ͷ�Ĵ�������һ�������Ʊ�������
	float c = 0b01000001;
	showFloatBits(c); 
	return 0;
} 