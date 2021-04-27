#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	node *a;
	for(int i = 0; i < 10; ++i) {
		a = cons(i, a);
	}
	print_list(a);
	int b = find_Nth_element(a, 5);
	printf("\nfifth element is: %d\n", b);
	return 0;
}
