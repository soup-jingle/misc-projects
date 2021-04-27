#include <stdio.h>
#include <stdlib.h>

void set(int* a, int val) {
	*a = val;
}

int main() {
	int a = 0;
	printf("before set: a=%d\n", a);
	set(&a, 7);
	printf("setting a to 7\n");
	printf("after set: a=%d\n", a);

	return 0;
}
