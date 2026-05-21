#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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
        char *myargs[3];
        myargs[0] = strdup("wc"); //program: "wc"
        myargs[1] = strdup("part3.c"); //arg: input file
        myargs[2] = NULL;           //mark end of array
        execvp(myargs[0], myargs);  //runs word count
        printf("this shouldn't print out");
    } else{
        //parent goes down this path (main)
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (PID:%d)\n", rc, rc_wait, (int) getpid());
    }
    return 0;
}
