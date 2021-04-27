#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main() {
	fork();
	fork();
	fork();
	fork();
	printf("exit()\n");
	exit(0);
}
