#include "sludge.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

unsigned long long file_count = 0;
unsigned long long entry_to_update = 0;
unsigned long HEADER = sizeof(unsigned long long);
unsigned int  ES = sizeof(Entry);
unsigned long header_pointer = 0;
unsigned long arx_start = 0;
unsigned long arx_pointer = 0;
unsigned long arx_pointer_extra = 0;
unsigned long arx_size = 0;

// For deleting
unsigned long long d_h = 0;
unsigned long d_o = 0;
unsigned long space_less = 0;
char *arx_name;

Entry er1; // Reserved space for entries
Entry er2; // (Was having segfault problems without these)

int main(int argc, char** argv) {
	int operation;
	int n;
	FILE *arx;
	header_pointer = HEADER;
	
	if(argc < 3) {
    output_usage();
		exit(0);
	}

	arx_name = argv[2];
	
	operation = arg_opt(argv[1]);
	if(operation == S_ERROR) return 1;
	//n = a_open(arx_name, arx);
	
 	if( (arx = fopen(arx_name, "rb+")) == NULL ) {
		printf("This file archive does not yet exist.\n");
		arx = fopen(arx_name, "wb+");
		n = F_NEW;
	}
	else n = F_EXISTS;
	
	if(n == F_EXISTS) {
		if(operation == S_CREATE) {
			printf("Current version of archive \"%s\" being overwritten!\n", arx_name);
		}
		else {
			/*rewind(arx);
				fread(&file_count, sizeof(unsigned long long), 1, arx);
				arx_start = (file_count / 10 + 1)*sizeof(Entry)+sizeof(unsigned long long);
				arx_pointer = arx_start;*/
			sludge_read(arx);
		}
	}
	
	//printf("operation = %d\n", operation);
	if(operation == S_CREATE) {
		Entry entry;
		file_count += (argc-3);
		printf("file count = %llu\n", file_count);
		rewind(arx);
		fwrite(&file_count, sizeof(unsigned long long), 1, arx);
		fwrite(&entry, sizeof(Entry), 10, arx);
		arx_start = 10*sizeof(Entry)+sizeof(unsigned long long);
		arx_pointer = arx_start;
		for(int i = 3; i < argc; ++i) {
			sludge_new_add_file(arx, argv[i]);
		}
		fclose(arx);
	}
	else if(operation == S_LIST) {
		sludge_list(arx);
		fclose(arx);
	}
	else if(operation == S_ADD) {
		for(int arg = 3; arg < argc; arg++) {
			sludge_process_file(argv[arg], &er1);
			int dupe = sludge_read_buffers_for_duplicate(arx, argv[arg], (&er1)->hash);
			if(dupe == 0) {
				sludge_add_entry(arx, &er1);
				sludge_add_file_contents(arx, (&er1)->name);
			}
		}
		fclose(arx);
	}
	else if(operation == S_REMOVE) {
		for(int arg = 3; arg < argc; arg++) {
			sludge_delete(arx, argv[arg]);
		}
	
		fseek(arx, 0, SEEK_END);
		unsigned long trunc = ftell(arx) - space_less;
		fclose(arx);
		truncate(arx_name, trunc);
	}
	else if(operation == S_EXTRACT) {
		if(argc > 3) {
			for(int arg = 3; arg < argc; arg++) {
				sludge_extract(arx, argv[arg]);
			}
		}
		else {
			sludge_extract_all(arx);
		}
	}

	return 0;
}

int arg_opt(char *opt) {
	if(0==strcmp(opt, "-c")) {
		printf("Create archive\n");
		return S_CREATE;
	}
  if(0==strcmp(opt, "-l")) {
		printf("List archive contents\n");
		return S_LIST;
	}
	if(0==strcmp(opt, "-a")) {
		printf("Add to archive\n");
		return S_ADD;
	}
	if(0==strcmp(opt, "-r")) {
		printf("Remove from archive\n");
		return S_REMOVE;
	}
	if(0==strcmp(opt, "-e")) {
		printf("Extract from archive\n");
		return S_EXTRACT;
	}
	printf("%s", opt);
	printf(" is not an argument\n\n");
  output_usage();
	return S_ERROR;
}

void sludge_read(FILE *file) {
	//printf("Sludge_read\n");
	rewind(file);
	fread(&file_count, sizeof(unsigned long long), 1, file);
	//fseek(file, HEADER, SEEK_SET);
	unsigned long min = 10*sizeof(Entry)+ HEADER;
	arx_start = file_count*sizeof(Entry) + HEADER;
	if(arx_start < min) arx_start = min;
	arx_pointer = arx_start;
	for(int i = 0; i < file_count; ++i) {
		fread(&er1, sizeof(Entry), 1, file);
		arx_pointer+=(&er1)->size;
		header_pointer += ES;
	}
	//printf("arx start: %lu\tarx ptr: %lu\n", arx_start, arx_pointer);
	//printf("done..\n");
}

void sludge_list(FILE *file) {
	fseek(file, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&er1, sizeof(Entry), 1, file);
		printf("%-20s %15lu bytes, %i links, hash = %llu\n", (&er1)->name, (&er1)->size, (&er1)->links, (&er1)->hash);
	}
}

void sludge_delete(FILE *file, char *filename) {
	int deleting = 0;
	int delete_data = 0;
	int entry_no = 0;
	
	fseek(file, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&er2, sizeof(Entry), 1, file);
		//printf("%s ?= %s\n", filename, (&er2)->name);
		if( 0 == strcmp(filename,(&er2)->name) ) {
			// For a given file name, this will only be true once
			// because of our checks when adding files, so there are
			// no duplicate name files.
			deleting = 1;
			entry_no = i;
			d_h = (&er2)->hash;
			d_o = (&er2)->offset;
			space_less = (&er2)->size;
			//printf("found it\n");
			break;
		}
	}
	fseek(file, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&er2, sizeof(Entry), 1, file);
		if(d_h == (&er2)->hash) {
			printf("Removing one link from \"%s\"\n", (&er2)->name);
			int l = (&er2)->links;
			l-=1;
			(&er2)->links = l;
			unsigned long rev = ftell(file) - ES;
			fseek(file, rev, SEEK_SET);
			fwrite(&er2, sizeof(Entry), 1, file);
			if( 0 != strcmp ((&er2)->name, filename))
				delete_data = -1;
		}
		if(deleting == 1 && i > entry_no) {
			fread(&er2, sizeof(Entry), 1, file);
			unsigned long rev = ftell(file) - (2*ES);
			fseek(file, rev, SEEK_SET);
		}
	}
	if(deleting == 1) {
		file_count--;
		fseek(file, 0, SEEK_SET);
		fwrite(&file_count, sizeof(unsigned long long), 1, file);
	}
	if(deleting == 1 && delete_data != -1) {
		// Only delete data if no other files link to same data
		printf("Last link to file is gone. Deleting!\n");
		fseek(file, HEADER, SEEK_SET);
		for(int i = 0; i < file_count; ++i) {
			fread(&er2, sizeof(Entry), 1, file);
			archive_relocate(&er2, d_o, file);
			d_o+=(&er2)->size;
		}
	}
	else {
		printf("Other entries point to the same data, or file not found, so not deleting it.\n");
	}
}

void sludge_extract(FILE *file, char *filename) {
	fseek(file, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&er1, sizeof(Entry), 1, file);
		if( 0 == strcmp((&er1)->name, filename) ) {
			sludge_extract_entry(file, &er1);
		}
	}
}

void sludge_extract_all(FILE *file) {
	fseek(file, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&er1, sizeof(Entry), 1, file);
		printf("Extracting \"%s\"\n", (&er1)->name);
		sludge_extract_entry(file, &er1);
	}
}

void sludge_extract_entry(FILE *file, Entry *entry) {
	char *extr = strcat(entry->name, ".ex");
	FILE *output = fopen(extr, "wb+");
	unsigned long return_to = ftell(file);
	char buffer[1024];
	fseek(file, entry->offset, SEEK_SET);
	for(int off = 0; off + 1024 < entry->size; off+=1024) {
		fread(buffer, 1024, 1, file);
		fwrite(buffer, 1024, 1, output);
	}
	int rem = entry->size % 1024;
	fread(buffer, rem, 1, file);
	fwrite(buffer, rem, 1, output);
	fseek(file, return_to, SEEK_SET);
}

void sludge_process_file(char *filename, Entry *entry) {
	//printf("sludge_process_file\n");
	FILE *file = fopen(filename, "rb+");
	unsigned long size = 0;
	unsigned long long int hash = 0;
	char c;
	
	if(file == NULL) {
		printf("Skipping nonexistent (or unopenable) file \"%s\".\n", filename);
		return;
	}
  
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	
	for(long i = 0; i < size; ++i) {
		fread(&c, 1, 1, file);
		hash += (int)c;
	}
	entry->size = size;
	entry->hash = hash;
	entry->offset = arx_pointer;
	entry->links = 1;
	strcpy( entry->name, filename);
	printf("%s %llu %lu %lu\n", entry->name, entry->hash, entry->size, entry->offset);
	
	fclose(file);
	//printf("done..\n");
}

int sludge_read_buffers_for_duplicate(FILE *archive, char *filename, unsigned long long hash) {
	Entry e;
	unsigned long b_s = 0;
	unsigned long long b_h = 0;
	unsigned long b_o = 0;
	unsigned short b_l = 0;
	int x = 0;
	int checker = 0;
	//printf("dupes\n");
	fseek(archive, HEADER, SEEK_SET);
	for(int i = 0; i < file_count; ++i) {
		fread(&e, sizeof(Entry), 1, archive);
		if( strcmp((&e)->name, filename) == 0 ) {
			checker = 2;
			printf("\"%s\" already exists in archive. Skipping.\n", filename);
		}
		if((&e)->hash == hash) {
			checker = 1;
			printf("\"%s\" data already exists under name \"%s\"\n", filename, (&e)->name);
			int j = (&e)->links;
			j++;
			(&e)->links = j;
			unsigned long rev = ftell(archive) - ES; // seeking from SEEK_CUR won't work...
			fseek(archive, rev, SEEK_SET);
			fwrite(&e, sizeof(Entry), 1, archive);
			printf("%s %llu %lu %lu\n", (&e)->name, (&e)->hash, (&e)->size, (&e)->offset);
			b_s = (&e)->size;
			b_h = (&e)->hash;
			b_l = (&e)->links;
			b_o = (&e)->offset;
		}
	}
	if(checker == 1) {
		(&e)->size = b_s;
		(&e)->hash = b_h;
		(&e)->links = b_l;
		(&e)->offset = b_o;
		strcpy( (&e)->name, filename);
		sludge_add_entry(archive, &e);
	}
	//printf("done\n");
	return checker;
}

void sludge_add_entry(FILE *archive, Entry *entry) {
	while(arx_start < header_pointer + ES) {
		fseek(archive, 0, SEEK_END);
		unsigned long end_of_arx = ftell(archive);
		fseek(archive, entry_to_update*sizeof(Entry)+HEADER, SEEK_SET);
		entry_to_update++;
		fread(&er1, sizeof(Entry), 1, archive);
		fseek(archive, -ES, SEEK_CUR);
		archive_relocate(&er1, end_of_arx, archive);
		(&er1)->offset = end_of_arx;
		arx_start += ((&er1)->size);
		fwrite(&er1, sizeof(Entry), 1, archive);
	}
	fseek(archive, header_pointer, SEEK_SET);
	fwrite(entry, sizeof(Entry), 1, archive);
	header_pointer+=ES;
	file_count++;
	fseek(archive, 0, SEEK_SET);
	fwrite(&file_count, sizeof(unsigned long long), 1, archive);
}

void sludge_new_add_file(FILE *archive, char *filename) {
	FILE *file = fopen(filename, "rb+");
	unsigned long size = 0;
	unsigned long long int hash = 0;
	char *c;
	
	if(file == NULL) {
		printf("Skipping nonexistent (or unopenable) file \"%s\".\n", filename);
		return;
	}
  
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	//printf("%lu\n", arx_pointer);
	fseek(archive, arx_pointer, SEEK_SET);
	
	for(long i = 0; i < size; ++i) {
		fread(c, 1, 1, file);
		hash += (int)*c;
		fwrite(c, 1, 1, archive);
		arx_pointer++;
	}
	//printf("arx off = %lu, arx ptr = %lu\n", arx_start, arx_pointer);
	(&er1)->size = size;
	(&er1)->hash = hash;
	(&er1)->offset = arx_pointer-size;
	(&er1)->links = 1;
	strcpy( (&er1)->name, filename);
	//printf("%s %llu %lu %lu\n", (&er1)->name, (&er1)->hash, (&er1)->size, (&er1)->offset);
	
	fseek(archive, header_pointer, SEEK_SET);
	fwrite(&er1, sizeof(Entry), 1, archive);
	header_pointer += ES;
	//printf("header ptr = %lu\n", header_pointer);*/
	//free(entry);

	fclose(file);
}

void sludge_add_file_contents(FILE *archive, char *filename) {
	FILE *file = fopen(filename, "rb+");
	char *c;
	
	if(file == NULL) {
		printf("Skipping nonexistent (or unopenable) file \"%s\".\n", filename);
		return;
	}
  
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	//printf("%lu\n", arx_pointer);
	fseek(archive, arx_pointer, SEEK_SET);
	
	for(long i = 0; i < size; ++i) {
		fread(c, 1, 1, file);
		fwrite(c, 1, 1, archive);
		arx_pointer++;
	}
	//printf("arx off = %lu\narx ptr = %lu\n", arx_start, arx_pointer);
	fclose(file);
}

void output_usage() {
  printf("Must specify at least two arguments.\n");
  printf("Commands: -c=create, -l=list, -a=add, -r=remove, -e=extract\n");
  printf("Usage: sludge -(command) archive_name [args...]\n");
}

void archive_relocate(Entry *entry, unsigned long new_position, FILE *arx) {
	char buffer[1024];
	int off;
	for(off = 0; off + 1024 < entry->size; off+=1024) {
		fseek(arx, (entry->offset)+off, SEEK_SET);
		fread(buffer, 1024, 1, arx);
		fseek(arx, new_position+off, SEEK_SET);
		fwrite(buffer, 1024, 1, arx);
		off+=1024;
	}
	int rem = entry->size%1024;
	fseek(arx, (entry->offset)+off, SEEK_SET);
	fread(buffer, rem, 1, arx);
	fseek(arx, new_position+off, SEEK_SET);
	fwrite(buffer, rem, 1, arx);

	entry->offset = new_position;
}
