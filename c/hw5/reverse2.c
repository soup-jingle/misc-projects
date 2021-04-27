#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

void reverse(char *infile_name) {
	long int p = 0;
	long int size;
	char temp;
	char *map;
  FILE *in = fopen(infile_name, "r+");
	
	size = fseek(in, 0L, SEEK_END);
	if(size == -1) printf("Error\n");
	size = ftell(in);
	--size;
	map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fileno(in), 0);
	
	while(p <= size / 2) {
		temp = map[p];
		map[p] = map[size-p];
		map[size-p] = temp;
		++p;
	}
	msync(map, size, MS_SYNC);
	munmap(map, size);
	fclose(in);
}

int main(int argc, char **argv) {
	reverse(argv[1]);
	return 0;
}
