#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"


int main(){
    pid_t child_pid;
    int status;
    int counter = 0;
    child_pid = fork();
    if(child_pid == 0){
        printf("Child process termination\n");
    }else{
        while(1);
    }
    return 0;
}