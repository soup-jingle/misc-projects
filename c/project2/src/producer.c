#include "lab2-api.h"
#include "synch.h"

main(int argc, char **argv) {
	lock_t mutex = argv[1];
	sem_t full = argv[2];
	sem_t empty = argv[3];
	char array[5] = argv[4];
	char hello[11] = argv[5];
	int aptr = argv[6];
	int ptr = argv[7];
	
	while(aptr < 11) {
		SemHandleWait(empty);
		LockHandleWait(mutex);
		array[ptr] = hello[aptr];
		aptr++;
		ptr = (ptr+1)%5
		LockHandleSignal(mutex);
		SemHandleSignal(full);
	}
}
