#include <stdio.h>
#include <stdlib.h>

void swap_ptrs(int** a, int** b) {
	int* temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int a = 1;
	int b = 2;

	printf("a=%d, b=%d\n", a, b);

	int *a_ptr = &a;
	int *b_ptr = &b;

	printf("a_ptr points to %d, b_ptr points to %d\n", *a_ptr, *b_ptr);
	printf("swap!\n");
	swap_ptrs(&a_ptr, &b_ptr);
	printf("a_ptr points to %d, b_ptr points to %d\n", *a_ptr, *b_ptr);
	
	return 0;
}
