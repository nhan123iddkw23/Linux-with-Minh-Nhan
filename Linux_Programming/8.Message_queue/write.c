#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> /* Defines O_* constants */
#include <sys/stat.h> /* Defines mode constants */
#include <mqueue.h>
struct mq_attr attr,attrd;

int main(){
    char send[10] = "LoveLan\n";
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 10;
    attr.mq_curmsgs = 0;
    mqd_t mqd = mq_open("/Minh_Nhan",O_RDWR|O_CREAT, 0666,&attr);
    if(mqd == -1){
        perror("mq_open");
    }
    if(mq_getattr(mqd,&attr) == -1){
        perror("mq_getattr");
    }
    if(attr.mq_flags == 0){
        printf("O_BLOCKING\n");
    }else{
        printf("O_NONBLOCK\n");
    }
    printf("Maximum of message on queue %ld\n",attr.mq_maxmsg);
    printf("Max message size %ld\n",attr.mq_msgsize);
    printf("# of messgae currently on queue %ld\n",attr.mq_curmsgs);
    if(mq_send(mqd,send,sizeof(send),1) == -1){
        perror("mq_send");
    }else{
        perror("mq_send");
    }
    //mq_unlink("/Minh_Nhan");
}