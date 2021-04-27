#include <stdio.h>
#include <stdlib.h>

void reverse(char *infile_name, char *outfile_name) {
	int check;
	unsigned char c;
	FILE *in = fopen(infile_name, "r");
	FILE *out = fopen(outfile_name, "w");
	check = fseek(in, 0L, SEEK_END);
	if(check == -1) printf("Error\n");
	//printf("%ld\n", ftell(in));

	int p, m;
	m = ftell(in);
	p = 0;
	
	while(m >= -p) {
		fread(&c, 1, 1, in);
		if(c != 0) fwrite(&c, 1, 1, out);
		fseek(in, p--, SEEK_END);
	}
	fread(&c, 1, 1, in);
	fwrite(&c, 1, 1, out);
	fclose(in);
	fclose(out);
}

int main(int argc, char **argv) {
	reverse(argv[1], argv[2]);
	return 0;
}
