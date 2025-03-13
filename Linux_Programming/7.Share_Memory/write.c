#include "fcntl.h"
#include "sys/stat.h"
#include "sys/mman.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"
int main(){
    int fd_open = 0;
    char *data = "Minh Nhan love you\n";
    void *ptr;
    fd_open = shm_open("/Nhandm",O_RDWR|O_CREAT,0666);
    if(fd_open == -1){
        perror("shm_open:");
    }
    ftruncate(fd_open,20);
    ptr = mmap(0,100,PROT_WRITE,MAP_SHARED,fd_open,0);
    strcpy(ptr,data);
    
}