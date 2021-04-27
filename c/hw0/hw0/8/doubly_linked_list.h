#include <stdio.h>
#include <stdlib.h>

#ifndef __BUNETIC_DOUBLY_LINKED_LIST__
#define __BUNETIC_DOUBLY_LINKED_LIST__

typedef struct listnode {
  int val;
	struct listnode* prev;
	struct listnode* next;
} node;

node* add_head(int value, struct listnode* head);

node* add_tail(int value, struct listnode* head);

void print_list(struct listnode* head);

void swap_nodes(node** a, node** b);

node* reverse(struct listnode* head);

int is_palindrome(struct listnode* head);

#endif
