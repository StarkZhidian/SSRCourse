

#include <stdio.h>

void translate(int num) {
	if (num == 0) {
		return ;
	}
	translate(num / 2);
	printf("%d", num & 1);
}

int main() {
	translate(728);
	return 0;
} 
