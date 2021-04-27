#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
int c;

int main() {
  pthread_t thread1, thread2, thread3;
	void *f1();
	sem_init(&mutex, 1, 1);
	c = 1;
	pthread_create(&thread1, NULL, f1, 1);
	pthread_create(&thread2, NULL, f1, 2);
	pthread_create(&thread3, NULL, f1, 3);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);

  return 0;
}

void *f1(int x) {
	int waiting = 1;
	while(waiting) {
		sem_wait(&mutex);
		if(x == c) {
			printf("%d\n", x);
			c++;
			waiting = 0;
			sem_post(&mutex);
		}
	}
	pthread_exit(0);
}
