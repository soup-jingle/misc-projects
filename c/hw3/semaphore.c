#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"

pthread_mutex_t mutex;

typedef struct semaphore {
	Queue wait;
	int count;
} Semaphore;

void sem_init(Semaphore *s, int i) {
	qInit(&s->wait);
	s->count = i;
	pthread_mutex_init(&mutex, NULL);
}

void sem_wait(Semaphore *s) {
	Elt *e;
	pthread_mutex_lock(&mutex);
	s->count -= 1;
	if(s->count < 0) {
		qNewElt(e, (void *)getpid());
		qInsertLast(&s->wait, e); 
	}
}

void sem_signal(Semaphore *s) {
	
}
