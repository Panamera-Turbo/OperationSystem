#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void main()
{
    pid_t pid = 0;
    int pipefd[2];//定义文件描述符，[0]是读端；[1]是写端。
    char c_buf[100];//缓冲区
    /*创建管道*/
    pipe(pipefd);

    pid = fork();

    if(pid == 0)
    {
        /*fork1-w*/
        write(pipefd[1], "Child process 1 is sending a message!",37);
        wait(NULL);
        close(pipefd[1]);
        exit(0);        
    }   


    pid_t pid2 = fork();

    if(pid2 == 0)
    {
        /*fork1-w*/
        write(pipefd[1], "Child process 2 is sending a message!",37);
        wait(NULL);
        close(pipefd[1]);
        exit(0);        
    }   

    if(pid > 0)
    {
        /*parent-r*/
        read(pipefd[0], c_buf, 37); 
        printf( "%s\n", c_buf);
        read(pipefd[0], c_buf, 37); 
        printf( "%s\n", c_buf);
        close(pipefd[0]);
        exit(0);
    }
}