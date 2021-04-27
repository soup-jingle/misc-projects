#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct semaphore {
	int count;
	pthread_cond_t condition;
	pthread_mutex_t mutex;
} Semaphore;

void sem_init(Semaphore *sem, int value) {
	sem = malloc(sizeof(Semaphore));
	pthread_mutex_init(&sem->mutex, NULL);
	pthread_cond_init(&sem->condition, NULL);
	sem->count = value;
}

void sem_wait(Semaphore *sem) {
	pthread_mutex_lock(&sem->mutex);
	sem->count--;
	if(sem->count < 0) {
		pthread_cond_wait(&sem->condition, &sem->mutex);
	}
	pthread_mutex_unlock(&sem->mutex);
}

void sem_signal(Semaphore *sem) {
	pthread_mutex_lock(&sem->mutex);
	sem->count++;
	pthread_cond_signal(&sem->condition);
	pthread_mutex_unlock(&sem->mutex);
}

/**********************************************/
/* Main Program *******************************/
/**********************************************/

Semaphore aArrived;
Semaphore bArrived;

int main() {
	pthread_t thread_a, thread_b;
	sem_init(&aArrived, 0);
	sem_init(&bArrived, 0);
	
	void *a();
	void *b();
	pthread_create(&thread_a, NULL, a, NULL);
	pthread_create(&thread_b, NULL, b, NULL);
	pthread_join(thread_a, NULL);
	pthread_join(thread_b, NULL);

  return 0;
}

void *a(void *v) {
	printf("a1\n");
	sem_signal(&aArrived);
	sem_wait(&bArrived);
	printf("a2\n");
	pthread_exit(0);
}

void *b(void *v) {
	printf("b1\n");
	sem_signal(&bArrived);
	sem_wait(&aArrived);
	printf("b2\n");
	pthread_exit(0);
}
