#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

pthread_mutex_t chopstick[6];

void *eat_think(void *arg)
{
	char phi = *(char *)arg;
	int left,right; 
	switch (phi){
		case 'A':
			left = 5;
			right = 1;
			break;
		case 'B':
			left = 1;
			right = 2;
			break;
		case 'C':
			left = 2;
			right = 3;
			break;
		case 'D':
			left = 3;
			right = 4;
			break;
		case 'E':
			left = 4;
			right = 5;
			break;
	}

	int i;
	for(int ii = 0; ii < 300; ii++)

	{
		usleep(30000); 
		int my_left = (left == 1) ? 5 : left - 1;
		if(pthread_mutex_trylock(&chopstick[my_left]) == EBUSY){
			continue; 
		}else{
			pthread_mutex_unlock(&chopstick[my_left]);
			pthread_mutex_lock(&chopstick[left]);
		}	

		printf(" %c fetches chopstick %d\n", phi, left);

		if (pthread_mutex_trylock(&chopstick[right]) == EBUSY){ //拿起右手的筷子	
			pthread_mutex_unlock(&chopstick[left]); //如果右边筷子被拿走放下左手的筷子
			continue;
		}
		
		printf("  %c fetches chopstick %d\n", phi, right);
		printf("  %c is eating.\n",phi);
		usleep(30000); //吃饭
		pthread_mutex_unlock(&chopstick[left]); //放下左手的筷子
		printf("  %c release chopstick %d\n", phi, left);
		pthread_mutex_unlock(&chopstick[right]); //放下左手的筷子
		printf("  %c release chopstick %d\n", phi, right);
 
	}
}
int main(){
	pthread_t A,B,C,D,E; //5个哲学家
 
	for (int i = 0; i < 5; i++)
		pthread_mutex_init(&chopstick[i],NULL);

	pthread_create(&A,NULL, eat_think, "A");
	pthread_create(&B,NULL, eat_think, "B");
	pthread_create(&C,NULL, eat_think, "C");
	pthread_create(&D,NULL, eat_think, "D");
	pthread_create(&E,NULL, eat_think, "E");
 
	pthread_join(A,NULL);
	pthread_join(B,NULL);
	pthread_join(C,NULL);
	pthread_join(D,NULL);
	pthread_join(E,NULL);
	return 0;
}