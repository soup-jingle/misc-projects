#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int main() {
	node *a;
	for(int i = 0; i < 4; ++i) {
		
		a = add_tail(i*3, a);
		a = add_head(i-1, a);
	}
	printf("before: ");
	print_list(a);
	printf("\nafter: ");
	print_list(reverse(a));
	printf("\n");
	return 0;
}
