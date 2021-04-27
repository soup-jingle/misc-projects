#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
	node *a;
	for(int i = 0; i < 10; ++i) {
		a = cons(i, a);
	}
	print_list(a);
	int b = remove_Nth_element(a, 5)->car;
	printf("\nremoving element 5");
	printf("\nelement removed is: %d\n", b);

	print_list(a);
	printf("\n");

	b = remove_Nth_element(a, 2)->car;
	printf("\nremoving element 2");
	printf("\nelement removed is: %d\n", b);

	print_list(a);
	printf("\n");
	
	return 0;
}
