#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "signal.h"

void sig_handler1(int num){
    printf("Hi i'm Nhan %d\n",num);
}


void sig_handler2(int num){
    printf("Love you %d\n",num);
}


void sig_handler3(int num){
    printf(" Lan %d\n",num);
}

int main(){
    if(signal(SIGINT,sig_handler1) == SIG_ERR){
        printf("Cannot handle sig_handler\n");
        return 0;
    }
    signal(SIGKILL,sig_handler2);
    signal(SIGTERM,sig_handler3);
    while(1){
        printf("Minh Nhan la so 1\n");
        sleep(1);
    }
    return 0;
}