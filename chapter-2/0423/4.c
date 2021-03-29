#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MSGFLAG 0
// #define MSGKEY 1024
/*
    用Linux的消息队列机制编程实现生产者-消费者问题。
*/
typedef struct msg_buffer
{
    
}msg_buffer;
//--------------------------------
typedef struct process_block
{
    /* data */
}process_block;
//--------------------------------
typedef struct msgstru{
    long mtype;
    char mtext[2048];
}my_msg;

//------------------------------------------------------------------
void produce(){ //生产者
    
}

void consume(){ //消费者

}
//------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    int creat_flag;
    key_t msg_key = IPC_PRIVATE;
    // int msg_flag = 0;

    printf("%d\n", msg_key);//测试，待注释

    creat_flag = msgget(msg_key, IPC_CREAT | IPC_EXCL); //没有则创建，有则出错


    if(creat_flag < 0){
        printf("creat_flag = %d\n", creat_flag);
        printf("fail to creat!\n");
        return -1;
    }

    
    return 0;
}
