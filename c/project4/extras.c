/*unsigned long long int sludge_hash() { // pass file in mem
	unsigned long long int hash_val = 0;
	int power = 1;
	char c;
	// get max file size
	// loop through char, add char value to hash
	// for(int i = 0; i < max; i++) {
	//   power = ((power % 5) + 1); // 'power' goes 1 to 5
	//   c = ;
	//   hash_val += pow((int)c, power);
	// }
	return hash_val;
}*/

/*void sludge_read(FILE *file, Node *head) {
	//fread(&entry_count, sizeof(int), 1, file);
	//Entry *entrys = malloc(sizeof(Entry) * entry_count);
	for(int i = 0; i < entry_count; ++i) {
		fread(entrys, sizeof(Entry), entry_count, file);
		}
}*/

/*void read_entry(Entry *head) {
	Entry *entry = malloc(sizeof(Entry));
	// read Entry from file
	// entry->next = *head;
	// entry->size = ;
	// entry->hash = ;
	// head = entry;
	}*/

Node *make_node(Entry *entry, Node *head) {
	Node *node = malloc(sizeof(Node));
	node->entry = entry;
	node->next = head;
	return node;
}

void traverse_list(Node *head) {
	while(head != NULL) {
		printf("%s\n", head->entry->name);
	}
}

void sludge_read(FILE *file, Node *head) {
  fread(&file_count, sizeof(unsigned long long), 1, file);
	printf("READ says file count = %llu\n", file_count);
	//Entry *entries  = malloc(sizeof(Entry) * file_count);
	for(int i = 0; i < file_count; ++i) {
		Entry *e = malloc(sizeof(Entry));
		/*fread(entries, sizeof(Entry), file_count, file);
			head = make_node(&entries[i], head);*/
		fread(e, sizeof(Entry), file_count, file);
		head = make_node(e, head);
		printf("%s\n", e->name);
		printf("%s\n", head->entry->name);
	}
	//traverse_list(head);
}
