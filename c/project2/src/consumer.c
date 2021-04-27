#include "lab2-api.h"
#include "synch.h"

main(int argc, char **argv) {
	lock_t mutex = argv[1];
	sem_t full = argv[2];
	sem_t empty = argv[3];
	char array[5] = argv[4];
	int ptr = argv[5];
	while(1) {
		SemHandleWait(full);
		LockHandleWait(mutex);
		Printf("%s\n", array[ptr]);
		ptr = (ptr+1)%5;
		LockHandleSignal(mutex);
		SemHandleSignal(empty);
	}
}
