#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 100000
FILE *out;
sem_t mutex;

int main() {
	pthread_t f3_thread, f2_thread, f1_thread;
	sem_init(&mutex, 1, 1);
	void *f1();
	int i = 0;
	out = fopen("numbers", "w+");
	pthread_create(&f1_thread, NULL, f1, &i);
	pthread_create(&f2_thread, NULL, f1, &i);
	pthread_create(&f3_thread, NULL, f1, &i);
	pthread_join(f1_thread, NULL);
	pthread_join(f2_thread, NULL);
	pthread_join(f3_thread, NULL);
	fclose(out);
	return 0;
}

void *f1(int *x) {
	while(*x < MAX) {
		sem_wait(&mutex); // Only one thread has access at a time
		fprintf(out, "%d\n", *x);
		(*x)++;
		sem_post(&mutex); // Allow access to other thread
	}
	pthread_exit(0);
}
