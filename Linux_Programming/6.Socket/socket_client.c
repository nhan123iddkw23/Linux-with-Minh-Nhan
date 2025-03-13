#include "stdio.h"
#include "string.h"
#include "time.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "netinet/ip.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "errno.h"

int main(){
    int sock_fd = -1; 
    struct sockaddr_in server_addr;
    char recv_buffer[1024] = {0};
    time_t ticks;

    memset(&server_addr,0,sizeof(server_addr));

    sock_fd = socket(AF_INET,SOCK_STREAM,0);  //[Protocol TCP/IP]
    server_addr.sin_family = AF_INET;    // ipV4
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000); // Ham tim port empty
    while(1){
    if(connect(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr)) == 0){
        read(sock_fd,recv_buffer,sizeof(recv_buffer));
        printf("\n%s\n",recv_buffer);
       // read(sock_fd,recv_buffer,sizeof(recv_buffer));
       // printf("\n%s\n",recv_buffer);
        }
    }
     close(sock_fd);
}
