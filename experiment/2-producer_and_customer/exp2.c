#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 10// length of buffer

pthread_mutex_t mutex, inLock, outLock;
sem_t empty, full;

int in, out, buffer[N];

void *produce(void *id){
	int i;
	// for (i = 0;i < 10;i ++)
    while (1)=[==[[==[o=[]]]]]
    {
		int tmp = *(int *)id, product;
		printf("Producer%d is trying producing...\n", tmp);
		sem_wait(&empty);
		pthread_mutex_lock(&inLock);
		pthread_mutex_lock(&mutex);
		usleep(3000);
		scanf("%d", &product);
		printf("Producer%d produces %d product successfully\n", tmp, product);
		buffer[in] = product;
		in = (in + 1) % N;
		sem_post(&full);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&inLock);
	}
}
void *consume(void *id){
	int i;
	// for (i = 0;i < 7;i ++)
    while (1)
    {
		int tmp = *(int *)id;
		printf("Consumer%d is trying consuming...\n", tmp);
		sem_wait(&full);
		pthread_mutex_lock(&outLock);
		pthread_mutex_lock(&mutex);
		usleep(rand()%10000 + 1000);// sleep for some time
		printf("Consumer%d consumes %d product successfully...\n", tmp, buffer[out]);
		out = (out + 1) % N;
		sem_post(&empty);
		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&outLock);
	}
}

int main(){
	freopen("data.txt", "r", stdin);
	
    pthread_t consumer[4], producer[3];
	
    sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);
	
    int producerId[] = {1, 2, 3};
	int consumerId[] = {1, 2, 3, 4};
	
    int i;
	for (i = 0;i < 3;i ++){
		int flag = pthread_create(producer + i, NULL, produce, (void *)(producerId + i));	
		if (flag != 0){
			printf("thread creates with error...\n");
			return 0;
		}
	}
	for (i = 0;i < 4;i ++){
		int flag = pthread_create(consumer + i, NULL, consume, (void *)(consumerId + i));
		if (flag != 0){
			printf("thread creates with error...\n");
			return 0;
		}
	}

	for (i = 0;i < 3;i ++) pthread_join(producer[i], NULL);
	for (i = 0;i < 4;i ++) pthread_join(consumer[i], NULL);

	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
