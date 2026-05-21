#include <stdio.h>
#include <stdlib.h>h
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int rc = fork();
    if(rc < 0){
        //fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0){
        //child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("./part4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");       //program: "wc"
        myargs[1] = strdup("part4.c");  //arg: file to count
        myargs[2] = NULL;               //mark end of array
        execvp(myargs[0], myargs);      //runs word count
        printf("this shouldn't print out");
    } else{
        //parent goes down this path (main)
        int rc_wait = wait(NULL);
    }
    return 0;
}
