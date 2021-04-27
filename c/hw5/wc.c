#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODE_FRESH 0   // wc.saved did not exist
#define MODE_NEW 1     // arg not in wc.saved
#define MODE_NOT_NEW 2 // arg is in wc.saved

#define TRUE 1
#define FALSE 0
typedef int bool;

typedef struct file_stat {
	char[255] name; // max file name length just in case
	unsigned int chars;
	unsigned int words;
	unsigned int lines;
} FileStat;

typedef struct overal_stat {
	unsigned int files;
	unsigned int chars;
	unsigned int words;
	unsigned int lines;
} OverallStat;

FileStat *stats[512]; // Reasonably large number, I assume

int do_count(char* filename) {
	char iter;
	int chars = 0;
	int words = 0;
	int lines = 0;
	bool on = FALSE;
	OverallStat *os = (OverallStat *)malloc(sizeof(OverallStat));
	int mode = do_input(stats, filename, os);
	FILE *file = fopen(filename, "r");
	if(file == NULL) return 1;
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
	if(mode != MODE_NOT_NEW) do_output();
	return 0;
}

int do_input(FileStat *stats[512], char *filename, OverallStat *os) {
	int i = 0;
	int mode = -1;
	FILE *in = fopen("wc.saved", "rb");
	if(in == NULL) return MODE_FRESH;
	while(fread(&stats[i], sizeof(FileStat), 1, in) == 1) {
		if(!stringcmp(stats[i]->name, filename))
			mode = MODE_NOT_NEW;
		os->files++;
		os->chars += stats[i]->chars;
		os->words += stats[i]->words;
		os->lines += stats[i]->lines;
	}
	fclose(in);
	if(mode == -1)
		return MODE_NEW;
	else return mode;
}

int do_output(char *name, int lines, int words, int chars, int mode) {
}

int main(int argc, char** argv) {
	if(argc == 2) {
		if(1 == do_count(argv[i])) {
			printf("Could not open file %s\n", argv[1]);
			return 1;
		}
	}
	else {
		printf("This utility takes exactly one filename argument\n");
		printf("Usage:\t./wc filename\n");
	}
	return 0;
}
