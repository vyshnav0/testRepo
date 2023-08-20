#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main(){
    pid_t pid;
    printf("hi\n");
    pid = fork();

    if (pid == 0){
        printf("Child process created %d\n",getpid());
        sleep(5);
        printf("ending child\n");
    }
    else if(pid >0){
        printf("This is parent process %d\n",getpid());
        wait(NULL);
        printf("ending parent\n");
    }
    else
        perror("fork");
}