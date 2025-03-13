#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"
#include "sys/wait.h"



int main(){
    pid_t child_pid;
    int status , rv;
    child_pid = fork();
    if(child_pid == 0){
        printf("My pid %d    My parent pid %d\n",getpid(),getppid());
        while(1);
        printf("Child process terminal after 5 seconds\n");
        sleep(5);
        exit(0);
    }else{
        rv = wait(&status);
        if(rv == -1){
            printf("Wait done\n");
        }
        printf("My pid %d, my child process %d\n",getpid(),rv);
        if(WIFEXITED(status)){
            printf("Normally terminaion, status = %d\n",WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){
            printf("Killed by signal, value = %d\n",WTERMSIG(status));
        }
    }
    return 0;
}