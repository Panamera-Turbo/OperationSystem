#include <stdio.h>
#include <unistd.h>
static int n = 0;

void my_thread_1(){
    n++;
}

void my_thread_2(){
    printf("%d", n);
    n = 0;
}

int main(int argc, char const *argv[])
{
    int p1, p2;
    
    p1 = fork();
    for(int i = 0; i < 10; i++){
        printf("%d:", i);
        my_thread_1;
        my_thread_2;
    }
    
    
    // sleep(2);
    // printf("%d", p1);
    return 0;
}
