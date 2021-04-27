#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

node* add_head(int value, struct listnode* head) {
	node *new_node = malloc(sizeof(node));
	new_node->val = value;
	new_node->next = head;
	if(head != NULL) {
		head->prev = new_node;
	}
	
	return new_node;
}

node* add_tail(int value, struct listnode* head) {
	
	node *new_node = malloc(sizeof(node));
	new_node->val = value;
	new_node->next = NULL;
	
	if(head == NULL)
		return new_node;
	
	node* iter = head;
	while(iter->next != NULL)
		iter = iter->next;
	
	iter->next = new_node;
	new_node->prev = iter;
	
	return head;
}

void print_list(struct listnode* head) {
	node *iter = head;
	while(iter != NULL) {
		printf("%d ", iter->val);
		iter = iter->next;
	}
	
}

void swap_nodes(node** a, node** b) {
	node* temp = *a;
	*a = *b;
	*b = temp;
}

node* reverse(struct listnode* head) {
	node *iter = head;
	node *new_head;
	while(iter != NULL) {
		swap_nodes(&(iter->prev), &(iter->next));
		new_head = iter;
		iter = iter->prev;
	}
	return new_head;
}

int is_palindrome(struct listnode* head) {
	node* b = reverse(head);

	node* a_ptr = head;
	node* b_ptr = b;

  while(a_ptr != b_ptr) {
		if(a_ptr->val != b_ptr->val) return 0;
		a_ptr = a_ptr->prev;
		if(a_ptr == b_ptr) return 1;
		b_ptr = b_ptr->next;
	}
	return 1;
}
