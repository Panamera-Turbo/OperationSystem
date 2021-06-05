#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // five philosopher
#define N_ROOM  4  //同一时间只允许４人用餐
#define left(phi_id) (phi_id+N-1)%N
#define right(phi_id) (phi_id+1)%N

// enum { think , hungry , eat  }phi_state[N];
sem_t chopstick[N];
sem_t room;

void thinking(int id){
    sleep(5);
    printf("哲学家[%d]在思考...\n", id);
}

void eating(int id){
    sleep(5);
    printf("哲学家[%d]在吃饭...\n", id);
}

void take_chopsticks(int id){
    //获取左右两边的筷子
    if((id%2) == 1){    
        sem_wait(&chopstick[left(id)]);
        sem_wait(&chopstick[right(id)]);
    }
    else{
        sem_wait(&chopstick[right(id)]);
        sem_wait(&chopstick[left(id)]);
    }
    printf("哲学家[%d]拿起筷子...\n", id);
}

void put_down_chopsticks(int id){
    printf("哲学家[%d]放下筷子...\n", id);
    sem_post(&chopstick[left(id)]);
    sem_post(&chopstick[right(id)]);
}

void* philosopher_work(void *arg){
    int id = *(int*)arg;
    printf("初始化[%d]号哲学家…… \n", id);
    while(1){
        thinking(id);
        sem_wait(&room);
        take_chopsticks(id);
        sem_post(&room);
        eating(id);
        put_down_chopsticks(id);
    }
}

int main(){
    pthread_t phiTid[N];
    int i;
    int err;
    int *id=(int *)malloc(sizeof(int)*N);

    //initilize semaphore
    for (i = 0; i < N; i++)
    {
        if(sem_init(&chopstick[i], 0, 1) != 0)
        {
            printf("init chopsticks error\n");
        }
    }

    sem_init(&room, 0, N_ROOM);

    for(i=0; i < N; ++i){
        //printf("i ==%d\n", i);
        id[i] = i;
        err = pthread_create(&phiTid[i], NULL, philosopher_work, (void*)(&id[i])); //这种情况生成的thread id是0,1,2,3,4
        if (err != 0)
            printf("system error \n");
    }

    while(1);
    for (i = 0; i < N; i++)
    {
        err = sem_destroy(&chopstick[i]);
        if (err != 0)
        {
            printf("can't destory semaphore\n");
        }
    }
    exit(0);
    return 0;
}