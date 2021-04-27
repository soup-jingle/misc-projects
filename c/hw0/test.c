#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	node *a;
	for(int i = 0; i < 10; ++i) {
		a = cons(i, a);
	}
	print_list(a);
	printf("n");
	find_Nth_element(a, 5);

	return 0;
}
