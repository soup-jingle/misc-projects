#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void print_list(struct listnode* head) {
	while(head != NULL) {
		printf("%d ", head->car);
		head = head->cdr;
	}
}

node* cons(int value, struct listnode* head) {
	node *new_node;
	new_node = malloc(sizeof(node));
	new_node->car = value;
	new_node->cdr = head;

	return new_node;
}

int find_Nth_element(struct listnode* head, int N) {
	node *n = head;
	for(int i = 1; i < N; ++i) {
		n = n->cdr;
	}
	return n->car;
}

node* remove_Nth_element(struct listnode* head, int N) {
	node *prev = malloc(sizeof(node));
	node *n = head;
	for(int i = 1; i < N; ++i) {
		prev = n;
		n = n->cdr;
	}
	prev->cdr = n->cdr;
	return n;
}

int find_Nth_to_last_element(struct listnode* head, int N) {
	node *reverse;
	node *a = head;
	while(a != NULL) {
		reverse = cons(a->car, reverse);
		a = a->cdr;
	}
	return find_Nth_element(reverse, N);
}
