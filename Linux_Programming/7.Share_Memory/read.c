#include "fcntl.h"
#include "sys/stat.h"
#include "sys/mman.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"
int main(){
    int fd_open = 0;
    char *ptr;
    char data[1024];
    fd_open = shm_open("/Nhandm",O_RDWR|O_CREAT,0666);
    if(fd_open == -1){
        perror("shm_open:");
    }
    ftruncate(fd_open,20);
    ptr = mmap(0,100,PROT_READ,MAP_SHARED,fd_open,0);
    strcpy(data,ptr);
    printf("%s",data);
    shm_unlink("/Nhandm");
}