#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define S_CREATE  0;
#define S_LIST    1;
#define S_ADD     2;
#define S_REMOVE  3;
#define S_EXTRACT 4;

typedef struct entry {
	char name[255];      // Max file name size (just in case)
	unsigned int offset; // Where to find the file block
	unsigned int size;   // Size of the block
	unsigned long long int hash;
} Entry;

typedef struct preamble {
	unsigned short int links;
} Preamble;

typedef struct list_node {
	Block *block;
	struct list_node *next;
} Node;

//Entry entries[4096];


int main() {
	/*unsigned long long m = ULLONG_MAX;
	//m++;
	printf("%llu\n%lu\n", m, sizeof(Entry));
	FILE *file0 = fopen("test.txt", "a");
	fclose(file0);
	FILE *file = fopen("test.txt", "r+");
	fwrite(&m, sizeof(long long unsigned int), 1, file);
	Block *block = malloc(sizeof(Block));
	block->size = 70;
	block->links = 1;
	block->hash = 77;
	fwrite(block, sizeof(Block), 1, file);
	char *chars = "hello worldxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	fwrite(chars, 40, 1, file);
	fclose(file);

	Block block2;
	unsigned long long int n;
	file = NULL;
	file = fopen("test.txt", "r");
	int x = fread(&n, sizeof(unsigned long long int), 1, file);
	printf("fread returns %d\n", x);
	x = fread(&block2, sizeof(Block), 1, file);
	printf("fread returns %d\n", x);
	printf("n=%llu\n", n);*/

	char *f = "test2.txt";
	char *h = "HELLO WORLD";
	char *h2;
	FILE *file = fopen(f, "a");
	fclose(file);
	file = fopen(f, "r+");
	fwrite(&h, 12, 1, file);
	fwrite(&h, 12, 1, file);
	//ftruncate(fileno(file), 12);
	fclose(file);

	truncate(f, 12);

	FILE *file0 = NULL;
	file0 = fopen(f, "r+");
	fread(&h2, 12, 1, file0);
	printf(h2);
	fclose(file0);
	return 0;
}
