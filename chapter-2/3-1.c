#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
/*
    作业3
    第1小题：
    将上页中的例子在Linux操作系统中运行，并得出执行结果，学会 wait4函数和fork函数的功能和使用方法。
*/

int main(){
    int child;
    char *args[] = {"/bin/echo", "Hello,", "World!", NULL};
        
    if (!(child = fork())){    //子进程从fork返回时，返回值为0;
        /* child */             //父进程从fork()返回时，返回值为子进程的id时，非0。
        printf("pid %d: %d is my father\n", getpid(), getppid());
        execve("/bin/echo", args, NULL);
        printf("pid %d: I am back, something ong!\n", getpid());
    }
    else{
        int myself = getpid();
        printf("pid %d: %d is my son\n", myself, child);
        wait4(child, NULL, 0, NULL);
        printf("pid %d: donc\n", myself);
    }
    return 0;
}