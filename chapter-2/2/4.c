#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/msg.h>
#include <sys/ipc.h>

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
typedef struct my_msg{
    int msg_type;
    char msg_text;
}my_msg;

//------------------------------------------------------------------
void produce(){
    
}

void consume(){

}
//------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    
    return 0;
}
