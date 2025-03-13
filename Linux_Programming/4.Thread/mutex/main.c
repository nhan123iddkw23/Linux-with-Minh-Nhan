#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "string.h"


pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

int counter = 2;

static void *handler_th1(void *args){
    pthread_mutex_lock(&lock1);
    printf("Thread1 handler, counter: %d\n",++counter);
    sleep(5);
    pthread_mutex_unlock(&lock1);
}

static void *handler_th2(void *args){
    pthread_mutex_lock(&lock1);
    printf("Thread2 handler, counter: %d\n",++counter);
    pthread_mutex_unlock(&lock1);
}


int main(){
    int ret;
    pthread_t thread_id1, thread_id2;
    if(ret == pthread_create(&thread_id1,NULL,&handler_th1,NULL)){
        printf("Error number %d\n",ret);
    }
    if(ret == pthread_create(&thread_id2,NULL,&handler_th2,NULL)){
         printf("Error number %d\n",ret);   
    }
    sleep(2);
    while(1);
    return 0;
}