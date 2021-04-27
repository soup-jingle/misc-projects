#include <stdio.h>
#include <stdlib.h>

#ifndef __BUNETIC_BINARY_TREE__
#define __BUNETIC_BINARY_TREE__

typedef struct treenode {
	int value;
	struct treenode *left;
	struct treenode *right;
} treenode;

treenode* insert(int value, treenode* root);

void inorder_print(treenode* root);

void nr_inorder_print(treenode* root);

//******************************************
//Stack:

typedef struct stack_el{
  treenode* value;
	struct stack_el* rest;
} stack_el;

stack_el* push(treenode* value, stack_el* stack);

treenode* pop(stack_el** stack);

#endif
