#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

treenode* insert(int value, treenode* root) {
	if(root == NULL) {
		treenode* n = malloc(sizeof(treenode));
		n->value = value;
		n->right = NULL;
		n->left = NULL;
		return n;
	}
	if(value <= root->value)
		root->left = insert(value, root->left);
	else
		root->right = insert(value, root->right);
}

void inorder_print(treenode* root) {
	if(root == NULL) return;
	if(root->left != NULL)
	  inorder_print(root->left);  // Recurse down left side
	printf("%d ", root->value);   // Then print this value
	if(root->right != NULL)
		inorder_print(root->right); // Then recurse down right side
	
}

void nr_inorder_print(treenode* root) {
	treenode* iter = root;
	stack_el* stack = NULL;
	while(1) {  // Loop until stack empty
		if(iter != NULL) {
			stack = push(iter, stack);
			iter = iter->left;  // Push left subtree onto stack
		}
		else {
			if(stack != NULL) {
				iter = pop(&stack);
				printf("%d ", iter->value);  // Print when not left subtree
				iter = iter->right; // Then push right subtree onto stack
			}
			else break;  // Stack empty
		}
	}
}

//************************************************
// Stack:

stack_el* push(treenode* value, stack_el* stack) {
	stack_el *se = malloc(sizeof(stack_el));
	se->value = value;
	se->rest = stack;
	return se;
}

treenode* pop(stack_el** stack) {
	treenode* top = (*stack)->value;
	*stack = (*stack)->rest;
	return top;
}
