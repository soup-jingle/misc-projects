#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	char dest[124];
	char buffer[] = "lorem ipsum |\nusernames, passwords,\nother totally sensitive data,\nsome not-so-sensitive data,\nother random things.";
	char src[] = "hello world";

	int len = strlen(src);
	printf("src = \"%s\" (%lu bytes)\n", src, sizeof(src));
	printf("copy %d bytes from src to buffer\n", len);
	memcpy(buffer, src, strlen(src));
	printf("copy 124 bytes from buffer to dest\n");
	memcpy(dest, buffer, 124);
	printf("\ndest:\n%s\n", dest);
	return 0;
}
