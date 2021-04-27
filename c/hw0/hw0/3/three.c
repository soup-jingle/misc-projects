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

	int *a_ptr = &a;
	int *b_ptr = &b;

	printf("%d  %d\n", *a_ptr, *b_ptr);
	swap_ptrs(&a_ptr, &b_ptr);
	printf("%d  %d\n", *a_ptr, *b_ptr);
	
	return 0;
}
