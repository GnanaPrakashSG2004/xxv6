#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    if(argc<=2){
        fprintf(2,"strace: invalid number of arguments");
        exit(1);
    }
    trace(atoi(argv[1]));
    if(exec(argv[2],&argv[2]) == -1){
        fprintf(2,"exec: unable to find %s\n",argv[2]);
        exit(1);
    };
    exit(0);
}