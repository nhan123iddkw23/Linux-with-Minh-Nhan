#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd;
    int read_file, write_file;
    char buff[20] = "Minh Nhan la so 1\n";
    fd = open("bbb.txt",O_RDWR|O_CREAT,0667);
    if(fd == -1){
        perror("Error");
    }else{
        perror("Message");
        lseek(fd, 2, SEEK_CUR);
        write_file = (fd,buff,strlen(buff));
        printf("Write %d bytes to nhan.txt",write_file);
    }
    close(fd);
}