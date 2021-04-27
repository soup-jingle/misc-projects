#include "lab2-api.h"
#include "producer.c"
#include "consumer.c"
#include "synch.h"

main(int argc, char **argv) {
	if(argc!=3) {
		Printf("Must provide value for number of producers and consumers to spawn.\n");
		exit();
	}
	int p = argv[1];
	int c = argv[2];
	char hello[] = "hello world";
	int h = 0;
	int x = 0;
	int y = 0;

	sem_t full = SemCreate(0);
	sem_t empty = SemCreate(5);
	lock_t mutex = LockCreate();

	int i;
	for(i = 0; i < p; i++) {
		process_create("producer.dlx.obj", mutex, full, empty, array, hello, h, x, NULL);
	}
	for(i = 0; i < c; i++) {
		process_create("consumer.dlx.obj", mutex, full, empty, array, y, NULL);
	}
}
