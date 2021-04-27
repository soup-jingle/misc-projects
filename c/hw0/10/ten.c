#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main() {

  treenode* t; // Makes a NULL tree;
	t = insert(100, t);
	insert(75, t);
	insert(50, t);
	insert(125, t);
	insert(25, t);
	insert(150, t);

	nr_inorder_print(t);
	printf("\n");
	//inorder_print(t);
	
	return 0;
}
