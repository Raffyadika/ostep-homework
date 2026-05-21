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
        printf("Child: sebelum close stdout\n");

        close(STDOUT_FILENO); // tutup stdout

        // Coba printf setelah stdout ditutup
        printf("Child: ini tidak akan muncul\n");

    } else {
        // PARENT
        wait(NULL);
        printf("Parent: selesai\n");
    }

    return 0;
}