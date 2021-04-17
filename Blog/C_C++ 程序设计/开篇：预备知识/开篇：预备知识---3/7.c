#include <stdio.h>

void showBits(short a) {
	int size = sizeof(a) * 8;
	int i;
	for (i = 0; i < size; i++) {
		printf("%d", (a >> (size - 1 - i)) & 1);
	}
}

int main() {
	short valueA = 0b100000010000000;
	short valueB = 0b101101100000000;
	short s = valueA + valueB;
	printf("a = %d\n", valueA);
	printf("b = %d\n", valueB);
	printf("a + b = %d\n", s);
	return 0;
} 
