#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int x = 100;

    printf("Sebelum fork, x = %d, PID(%d)\n", x, getpid());

    pid_t pid = fork();

    if(pid < 0){
        printf("fork gagal");
        return 1;
    }
    else if(pid == 0){
        //CHILD
        printf("Child awal, x = %d, PID(%d)\n", x, getpid());
        x = 200;
        printf("Child akhir, x = %d, PID(%d)\n", x, getpid());
    }
    else{
        //PARENT
        printf("Parent awal, x = %d, PID(%d)\n", x, getpid());
        x = 300;
        printf("Parent akhir, x = %d, PID(%d)\n", x, getpid());
    }
    return 0;
}