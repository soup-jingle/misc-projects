#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	fork();
	printf("%d\n", getpid());
	return 0;
}
