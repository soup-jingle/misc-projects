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
