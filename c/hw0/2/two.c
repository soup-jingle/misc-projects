#include <stdio.h>
#include <stdlib.h>

void swap_ints(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int a = 0;
	int b = 1;
	printf("a=%d, b=%d\n", a, b);
	swap_ints(&a, &b);
	printf("swap!\n");
	printf("a=%d, b=%d\n", a, b);
	return 0;
}
