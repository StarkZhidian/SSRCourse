#include <stdio.h>

int main() {
    // 0b ��ͷ�Ĵ�������һ�������Ʊ�������
	int c = 0b01000001;
	float *cp = (float *)&c;
	// %.128f ��ʾ���һ����������������� 128 λС��
	printf("%.128f\n", *cp);
	return 0;
} 
