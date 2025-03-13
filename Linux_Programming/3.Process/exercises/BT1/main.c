#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"
#include "fcntl.h"

u_int8_t Tx_Buffer[12] = "I love lan";
char Rx_Buffer[12];
int Size_count = 0;
int main(){
    pid_t child_pid;
    int fd;
    child_pid = fork();
    if(child_pid == 0){ // Process child
        fd = open("hello.txt",O_RDONLY,0777);
        if(fd == -1){
            perror("ERROR OPEN FILE READ ONLY");
        }
        else{
            perror("Thanh cong doc file");
            Size_count = read(fd,Rx_Buffer,12);
            if(Size_count != 0){
               perror("None");
               printf("\n%s and %d",Rx_Buffer,Size_count); 
            }
        }
    }else{
       
        fd = open("hello.txt",O_WRONLY,0777);
        if(fd == -1){
            perror("ERROR OPEN FILE WRITE ONLY");
        }
        else{
            perror("Thanh cong ghi file");
        }
        write(fd,Tx_Buffer,12);
    }
    close(fd);
}