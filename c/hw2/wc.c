#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int bool;

void do_count_console() {
	char iter;
	int chars = 0;
	int words = 0;
	int lines = 1;
	bool on = FALSE;
	
	while((iter = fgetc(stdin)) != EOF) {
		++chars;
		if(iter == ' ' || iter == '\t' || iter == '\n') {
			if(on) ++words;
			if(iter == '\n') ++lines;
			on = FALSE;
		}
		else on = TRUE;
	}
	printf("\n\t%d\t%d\t%d\n", lines, words, chars);
}

void do_count(char* filename) {
	char iter;
	int chars = 0;
	int words = 0;
	int lines = 0;
	bool on = FALSE;
  FILE *file = fopen(filename, "r");
	while((iter = fgetc(file)) != EOF) {
		++chars;
		if(iter == ' ' || iter == '\t' || iter == '\n') {
			if(on) ++words;
			if(iter == '\n') ++lines;
			on = FALSE;
		}
		else on = TRUE; 
	}
	fclose(file);
	printf("\t%d\t%d\t%d\n", lines, words, chars);
}

int main(int argc, char** argv) {
	if(argc > 1) {
		for(int i = 1; i < argc; i++) {
			do_count(argv[i]);
		}
	}
	else {
		do_count_console();
	}
	return 0;
}
