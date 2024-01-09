#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    int pid = fork();
    int* x= (int *) 10;
    if(pid<0){
        return 0;
    }else if(pid == 0){
        printf("\n%d\n",*x);
    }else{
        int status;
        wait(&status);
    }
    exit(0);
}