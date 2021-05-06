#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <pthread.h>

#define bufferSize 10
#define msgMaxSize 110

int buffer[bufferSize];
int in, out, productNum, productId, queueId;

char bufferFree[] = "缓冲区空闲";

struct MSG{
	long type;
	char* text;
}msg;

void *produce();
void *consume();
int main(){
	pthread_t producer, consumer;

	queueId = msgget(0, IPC_CREAT | 0666);
	
	msg.type = 1;
	msg.text = bufferFree;
	msgsnd(queueId, (void *)&msg, strlen(msg.text), 0);

	pthread_create(&consumer, NULL, consume, NULL);
	pthread_create(&producer, NULL, produce, NULL);
	pthread_exit(NULL);
	msgctl(queueId, IPC_RMID, NULL);
	return 0;	
}
void *produce(){
	for (int i = 1;i <= 10;i ++){
		while(productNum == 10);
		msgrcv(queueId, (void *)&msg, strlen(bufferFree), 1, 0);

		productNum ++;
		productId ++;
		buffer[in] = productId;
		printf("produce %d product\n", buffer[in]);
		in = (in + 1) % bufferSize;
		
		msg.type = 1;
		msg.text = bufferFree;
		msgsnd(queueId, (void *)&msg, strlen(msg.text), 0);
	}
}
void *consume(){
	for (int i = 1;i <= 10;i ++){
		usleep(1);
		while(productNum == 0);
		msgrcv(queueId, (void *)&msg, strlen(bufferFree), 1, 0);
		
		productNum --;
		printf("costume %d product\n", buffer[out]);
		buffer[out] = 0;
		out = (out + 1) % bufferSize;

		msg.type = 1;
		msg.text = bufferFree;
		msgsnd(queueId, (void *)&msg, strlen(msg.text), 0);	
	}
}