#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h> 
void main(){ 
    pid_t pid; 
    
    printf("program is starting\n"); 
    
    pid=fork(); 
    switch(pid){ 
        case -1: exit(0); 
                break; 
        case 0: while(1){ 
                    sleep(1);
                    printf("hello world\n"); 
                }break; 
                
        default: sleep(10); //发出终止信号


    printf("结束子进程\n"); 
    kill(pid,SIGTERM); 
    break; 
    } 
}