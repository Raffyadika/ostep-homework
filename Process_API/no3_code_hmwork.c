//USE SLEEP

/*#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // CHILD
        printf("hello\n");

    } else {
        // PARENT
        sleep(1); // berharap child selesai dulu
        printf("goodbye\n");
    }

    return 0;
}*/


//USE SEMAPHORE

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // Buat semaphore, nilai awal 0 (parent langsung blokir)
    sem_t *sem = sem_open("/mysem", O_CREAT, 0644, 0);

    pid_t pid = fork();

    if (pid == 0) {
        // CHILD
        printf("hello\n");
        sem_post(sem); // beri sinyal ke parent: "aku sudah selesai"

    } else {
        // PARENT
        sem_wait(sem); // tunggu sinyal dari child
        printf("goodbye\n");

        sem_close(sem);
        sem_unlink("/mysem"); // hapus semaphore
    }

    return 0;
}