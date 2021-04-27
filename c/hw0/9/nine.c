#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main() {

	treenode* t; // Makes a NULL tree;
	t = insert(100, t); // First insert() makes a root
	insert(75, t);
	insert(50, t);
	insert(125, t);
	insert(25, t);
	insert(150, t);

	inorder_print(t);
	printf("\n");
	
	return 0;
}
