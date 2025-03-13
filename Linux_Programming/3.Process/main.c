#include "stdio.h"
#include "string.h"
#include "unistd.h"

 
int main(int n, char * arg[]){
   
    /*
    printf("So luong doi so la %d\n",n);
    for(int i = 0; i < n; i++){
        printf("Gia tri doi so la arg[%d] = %s\n",i+1,arg[i]);
    } */
    pid_t child_pid;
    int a = 0;
    printf("\nGia tri cua a : %d\n",a);
    child_pid = fork();  // neu child_pid = 0 -> la process con > 0 thuoc process cha
    if(child_pid == 0){
        printf("\nI'm the child process, count : %d\n",a);
        printf("My PID is: %d   My Parent PID: %d \n",getpid(),getppid());  // getpid()-> pid cua process hien tai
    } else{
        printf("I am the praent process, a = %d\n",++a);
        printf("My PID is: %d My Parent PID: %d\n",getpid(),getppid());
        //while(1);
    }
    return 0;
}
