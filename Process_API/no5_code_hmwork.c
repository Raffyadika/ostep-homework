#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork gagal!\n");
        return 1;

    } else if (pid == 0) {
        // CHILD
        printf("Child: PID saya = %d\n", getpid());

        // Apa yang terjadi kalau wait() dipanggil di child?
        pid_t ret = wait(NULL);
        printf("Child: hasil wait() = %d\n", ret);
        // child tidak punya anak, jadi wait() langsung return -1

    } else {
        // PARENT
        printf("Parent: menunggu child selesai...\n");

        pid_t ret = wait(NULL);
        printf("Parent: wait() return = %d\n", ret);
        // return nilai = PID dari child yang selesai
    }

    return 0;
}