#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "pthread.h"

pthread_t thread_id1, thread_id2,thread_id3;
int count = 0;
typedef struct {
    char name[30];
    char msg[30];
}thr_data_t;
/*
static void *thr_handler(void *args){
     pthread_t tid = pthread_self();
     thr_data_t *data = (thr_data_t *)args;

     if(pthread_equal(tid,thread_id1)){
         printf("I'm thread_id1\n\n");
     }else{
        printf("I'm thread_id2\n");
         printf("Hello %s, welcome to join %s\n",data->name,data->msg);
     }
 }
*/

static void *thr_handler(void *args){
     printf("Hi I'm thread 1\n");
}
static void *thr_handler3(void *args){
     printf("Hi I'm thread 3\n");
}
/*
static void *thr_handler2(void *args){
    while(1){
    printf("Hi I'm thread 2\n");
    sleep(1);
    };
}*/


int main(int argc, char const *argv[]){
    int ret;
    thr_data_t data = {0};

    //strncpy(data.name,"Minh Nhan",sizeof(data.name));
    //strncpy(data.msg,"Love Lan",sizeof(data.msg));

    if(ret == pthread_create(&thread_id1,NULL,&thr_handler,NULL)){
        printf("Error number %d\n",ret);
    }
    sleep(2);
    // if(ret == pthread_create(&thread_id2,NULL,&thr_handler2,NULL)){
    //     printf("Error number %d\n",ret);   
    // }
    //sleep(5);
    //pthread_cancel(thread_id2);
    //pthread_join(thread_id2,NULL);
    //printf("\nThread termination");
    while(1){
        if(ret = pthread_create(&thread_id3,NULL,&thr_handler3,NULL)){
           printf("Error number %d\n",ret);
           break;
        }
        count++;
        if(count % 1000 == 0){
               printf("Count : %d\n",count);
        }
        //pthread_join(thread_id3,NULL);    
    }
    return 0;
}
