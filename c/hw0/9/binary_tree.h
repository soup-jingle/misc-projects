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

#endif
