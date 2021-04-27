#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

int produce_item();
void insert_item(int item);
int remove_item();
int consume_item(int item);


sem_t mutex;
sem_t empty;
sem_t full;

int a[N];

int p;
int c;

int main() {
	pthread_t threadp1, threadp2, threadp3, threadc1, threadc2, threadc3;
	void *producer();
	void *consumer();
	
	sem_init(&mutex, 1,1);
	sem_init(&empty, 1, N);
	sem_init(&full, 1, 0);
	
	p = 0;
	c = 0;

	srand(0);

	pthread_create(&threadp1, NULL, producer, NULL);
	sleep(1);
	//pthread_create(&threadp2, NULL, producer, NULL);
	//pthread_create(&threadc3, NULL, consumer, NULL);
	//pthread_create(&threadc2, NULL, consumer, NULL);
	//sleep(1);
	//pthread_create(&threadp3, NULL, producer, NULL);
	pthread_create(&threadc1, NULL, consumer, NULL);
	pthread_join(threadp1, NULL);
	//pthread_join(threadp2, NULL);
	//pthread_join(threadp3, NULL);
	pthread_join(threadc1, NULL);
	//pthread_join(threadc2, NULL);
	//pthread_join(threadp3, NULL);

	return 0;
}

void *producer() {
	int item;
	for(int i = 0; i <= N; i++) {
		item = i; //produce_item();
		if(sem_trywait(&empty) < 0) {
			printf("Buffer is full.\n");
			sem_wait(&empty);
		}
		sem_wait(&mutex);
		insert_item(item);
		sem_post(&mutex);
		sem_post(&full);
	}
	pthread_exit(0);
}

void *consumer() {
	int item;
  for(int i = 0; i <= N+1; i++) {
		if(sem_trywait(&full) < 0) {
			printf("Buffer is empty.\n");
			sem_wait(&full);
		}
		sem_wait(&mutex);
		item = remove_item();
		sem_post(&mutex);
		sem_post(&empty);
		//consume_item(item);
	}
	pthread_exit(0);
}

void insert_item(int item) {
	printf("Producing item: %d\n", p);
	a[p] = item;
	p = (p+1)%N;
}

int remove_item() {
	printf("Consuming item: %d\n", c);
	int item = a[c];
	c = (c+1)%N;
	return item;
}
