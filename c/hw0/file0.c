void set(int* a, int val) {
	*a = val;
}

void swap_ints(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap_ptrs(int** a, int** b) {
	int* temp = *a;
	*a = *b;
	*b = temp;
}

deftype struct listnode {
  int val;
	struct listnode* next;
} node;

void print_list(struct listnode* head) {
	
}

int find_Nth_element(struct listnode* head, int N) {
	listnode node = *head;
	for(int i = 0; i < N; ++i) {
		node = *(node.next);
	}
	return node.head;
}

void remove_Nth_element(struct listnode* head, int N) {
	listnode node = *prev;
	listnode node = *head;
	for(int i = 0; i < N; ++i) {
		prev = node;
		node = *(node.next);
	}
	*(prev.next) = *(node.next);
}

deftype struct listnode {
	int val;
	struct doublelist *prev;
	struct doublelist *next;
} node;

void reverse(node** head) {
	
}

int is_palindrome(struct listnode* head) {
	
}

