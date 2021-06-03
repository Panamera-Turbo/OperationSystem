




#define left(phi_id) (phi_id+N-1)%N
#define right(phi_id) (phi_id+1)%N
N = 5
pthread_mutex_t forks[N]={PTHREAD_MUTEX_INITIALIZER};

void take_forks(int id){
    //获取左右两边的筷子
    //printf("Pil[%d], left[%d], right[%d]\n", id, left(id), right(id));
    if((id&1) == 1){
        sem_wait(&chopstick[left(id)]);
        sem_wait(&chopstick[right(id)]);
    }
    else{
        sem_wait(&chopstick[right(id)]);
        sem_wait(&chopstick[left(id)]);
    }
    //printf("philosopher[%d]  take_forks...\n", id);
}

void put_down_forks(int id){
    printf("philosopher[%d] is put_down_forks...\n", id);
    pthread_mutex_unlock(&forks[left(id)]);
    pthread_mutex_unlock(&forks[right(id)]);
}

void* philosopher_work(void *arg){
    int id = *(int*)arg;
    printf("philosopher init [%d] \n", id);
    while(1){
        thinking(id);
        take_forks(id);
        eating(id);
        put_down_forks(id);
    }
}