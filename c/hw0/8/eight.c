#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

void print_is_palindrome(int i) {
	if(i == 1)
		printf("is a palindrome\n");
	else printf("is not a palindrome\n");
}

int main() {
	node *a = NULL;
	for(int i = 0; i < 4; ++i) {	
		a = add_tail(i+1, a);
		a = add_head(i, a);
	}
	print_list(a);
	printf("\n");
	print_is_palindrome(is_palindrome(a));
	printf("\n");
	
	node *b = NULL;
	for(int i = 0; i < 4; ++i) {
		b = add_tail(i, b);
		b = add_head(i, b);
	}
	print_list(b);
	printf("\n");
	print_is_palindrome(is_palindrome(b));
	
	return 0;
}
