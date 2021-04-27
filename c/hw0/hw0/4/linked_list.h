#include <stdio.h>
#include <stdlib.h>

#ifndef __BUNETIC_LINKED_LIST__
#define __BUNETIC_LINKED_LIST__

typedef struct listnode {
  int car;
	struct listnode* cdr;
} node;

node* cons(int value, struct listnode* head);

void print_list(struct listnode* head);

int find_Nth_element(struct listnode* head, int N);

node* remove_Nth_element(struct listnode* head, int N);

int find_Nth_to_last_element(struct listnode* head, int N);

#endif
