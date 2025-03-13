#include "stdio.h"
#include "string.h"
#include "time.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "netinet/ip.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "errno.h"
#include <linux/if_link.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include "signal.h"
#include "stdbool.h"
#include <sys/types.h>
char My_Input[20];
struct sockaddr_in server_addr,client_addr;
struct ifaddrs *ifaddr, *ifa;
socklen_t client_addr_len = sizeof(client_addr);
int connectfd = -1; 
int listenfd = -1;
time_t ticks;
char send_buffer[1024] = {0};
char My_IP[20] = {0};
int family, s;
char host[100];
int option = 1;
bool check = true;


void Printf_My_IP(){
    if(getifaddrs(&ifaddr) == -1){
        perror("getifaddr");
        exit(0);
    }
    for(struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next){
        if(ifa->ifa_addr == NULL){
            continue;
        }
        family = ifa->ifa_addr->sa_family;
        if(family == AF_INET){
            s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, sizeof(host),NULL, 0, NI_NUMERICHOST);
                if (s != 0) {
                    printf("getnameinfo() failed: %s\n", gai_strerror(s));
                    exit(0);
                }

            printf("\t\taddress: <%s>\n", host);
        }
    }
}



int Input_To_User(){
    char client_ip[INET_ADDRSTRLEN] = {0};
    int client_host,server_host = 0;
    printf("******************MENU******************\n");
    printf("1 = Help                              :display user interface options\n");
    printf("2 = Myip                              :display IP address of this app\n");
    printf("3 = Myport                            :display listening port of this app\n");
    printf("4 = Connect <destination> <port no>   :connect to the app of another computer\n");
    printf("5 = List                              :list all the connections of this app\n");
    printf("6 = terminate <connection id>         :terminate a connection\n");
    printf("7 = send <connection id> <message>    :send a message to a connection\n");
    printf("0 = Exti\n");
    memset(&My_Input,0,sizeof(My_Input));
    printf("\nCommand: ");
    fgets(My_Input, sizeof(My_Input), stdin);
    if(My_Input[0] == '0'){
        return -1;
    }
    else if(My_Input[0] == '2'){
         Printf_My_IP();
    }
    else if(My_Input[0] == '3'){
        server_host = ntohs(server_addr.sin_port);
        printf("This Port of Server: %d\n",server_host);
    }
    else if(My_Input[0] == '4'){
        if (inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN) == NULL) {
            perror("inet_ntop");
        }
        // In ra địa chỉ IP của client
        client_host = ntohs(client_addr.sin_port);
        printf("This Port and IP Client: %d    <%s>\n",client_host,client_ip);
    }
    else if(My_Input[0] == '6'){ // Input == 6 terminate
        //shutdown(connectfd,SHUT_RDWR);
        printf("Disconnect Done\n"); 
        close(connectfd);
        connectfd = 0;
        sleep(3);
        if(listen(listenfd,10) < 0) {
            perror("listen: ");
        }else{
            printf("Listen Done\n");
        }
        connectfd = accept(listenfd,(struct sockaddr*)&client_addr,(socklen_t *)&client_addr_len);
        if(connectfd < 0){
            perror("accept");
        }   // block if not connect to server
        else
        {
            printf("ERROR\n");
        }
    }
    else if(My_Input[0] == '7'){ // Input == 7 Send data
        ticks = time(NULL);
        sprintf(send_buffer,"Server reply %s\n",ctime(&ticks));
        write(connectfd,send_buffer,sizeof(send_buffer));
    }   
}



int main(){
    memset(&server_addr,0,sizeof(server_addr));    
    listenfd = socket(AF_INET,SOCK_STREAM,0);  //[Protocol TCP/IP]
    server_addr.sin_family = AF_INET;    // ipV4
    server_addr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY; // inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000); //  Ham tim port empty
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
    bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    listen(listenfd,10);  // 10 - number client
    connectfd = accept(listenfd,(struct sockaddr*)&client_addr,(socklen_t *)&client_addr_len);   // block neu khong co connect
    while(1){
        if(Input_To_User() == -1){
         close(connectfd);
         return 0;
        }
    }

    close(listenfd);
}












