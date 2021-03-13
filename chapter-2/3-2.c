#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    第二章作业三
    第二问：
    调用wait3，wait4，waitpid的 功能和使用方法，他们都是指定要等待子进程结束，他们有何区别？编程练习这3个函数的使用。
*/

void my_wait3(){
    int child;
    char *args[] = {"/bin/echo", "Hello,", "wait3() !", NULL};
        
    if (!(child = fork())){    
        printf("pid %d: %d is my father\n", getpid(), getppid());
        // execve("/bin/echo", args, NULL);
        // printf("pid %d: I am back, something ong!\n", getpid());
    }
    else{
        int myself = getpid();
        printf("pid %d: %d is my son\n", myself, child);
        wait3(NULL, 0, NULL);
        printf("pid %d: donc\n", myself);
    }
    // return 0;
}

void my_wait4(){
    int child;
    char *args[] = {"/bin/echo", "Hello,", "World!", NULL};
        
    if (!(child = fork())){    
        printf("pid %d: %d is my father\n", getpid(), getppid());
        // execve("/bin/echo", args, NULL);
        // printf("pid %d: I am back, something ong!\n", getpid());
    }
    else{
        int myself = getpid();
        printf("pid %d: %d is my son\n", myself, child);
        wait4(child, NULL, 0, NULL);
        printf("pid %d: donc\n", myself);
    }
    // return 0;
}

void my_waitpid(){  //waitpid练习
    pid_t pc, pr;

    pc = fork();
    if(pc < 0 )
    {
            printf("Error fork\n");
            exit(1);
    }
    else if( pc == 0 )    /* 子进程 */
    {
        /* 子进程暂停5s */
        sleep(5);
        /* 子进程正常退出 */
        exit(0);
    }
    else    /* 父进程 */
    {
        /* 循环测试子进程是否退出 */
        do
        {
            /* 调用waitpid，且父进程不阻塞 */
            pr = waitpid(pc, NULL, WNOHANG);

            /* 若子进程还未退出，则父进程暂停1s */
            if( pr == 0 )
            {
                printf("The child process has not exited\n");
                sleep(1);
            }
        }while( pr == 0 );

        /* 若发现子进程退出，打印出相应情况 */
        if( pr == pc )
        {
            printf("Get child exit code: %d\n",pr);
        }
        else
        {
            printf("Some error occured.\n");
        }
    }
}

int main(int argc, char const *argv[])
{
    printf("practice function: wait3()\n");
    my_wait3();
    puts("");
    printf("practice function: wait4()\n");
    my_wait4();
    puts("");
    printf("practice function: pidwait()\n");
    my_waitpid();
    return 0;
}
