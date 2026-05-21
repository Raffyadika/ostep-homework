#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("Hello (PID:%d)\n", (int) getpid());
    int rc = fork();
    if(rc < 0){
        //fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        //child (new process)
        printf("child (PID:%d)\n", (int) getpid());
    } else{
        //parent goes down this path (main)
        printf("parent of %d (PID:%d)\n", rc, (int) getpid());
    }
    return 0;
}
