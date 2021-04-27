#include <stdio.h>
#include <stdlib.h>

#define S_ERROR       -1
#define S_CREATE       0
#define S_LIST         1
#define S_ADD          2
#define S_REMOVE       3
#define S_EXTRACT      4

#define F_NEW          0
#define F_EXISTS       1

typedef struct entry {
	char name[255]; // Max file name size (just in case)
	unsigned long offset; // Where to find the 'Block'
	unsigned long size;
	unsigned long long int hash;
	unsigned short links;
} Entry;


void output_usage();
int arg_opt(char *opt);
int a_open(char *name, FILE *file);
void sludge_read(FILE *file);
void sludge_list(FILE *file);
void sludge_delete(FILE *file, char *filename);
void sludge_add_entry(FILE *archive, Entry *entry);
void sludge_new_add_file(FILE *archive, char *filename);
void sludge_process_file(char *filename, Entry *entry);
void sludge_add_file_contents(FILE *archive, char *filename);
void sludge_extract(FILE *file, char *filename);
void sludge_extract_all(FILE *file);
void sludge_extract_entry(FILE *file, Entry *entry);
void sludge_process_file(char *filename, Entry *entry);
void archive_relocate(Entry *entry, unsigned long new_position, FILE *arx);
int sludge_read_buffers_for_duplicate(FILE *archive, char *filename, unsigned long long hash);
/*
Node *make_node();
Entry *make_entry();
*/
