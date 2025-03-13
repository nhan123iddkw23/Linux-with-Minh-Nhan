#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(){
    printf("Run command after 2 second\n");
    sleep(2);
    execl("/bin/ls","ls","-l","-h",NULL);
    return 0;
}

