#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // Buka file sebelum fork
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        printf("Gagal membuka file!\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork gagal!\n");
        return 1;

    } else if (pid == 0) {
        // CHILD
        char *msg = "Ini ditulis oleh CHILD\n";
        for (int i = 0; i < 5; i++) {
            write(fd, msg, strlen(msg));
        }

    } else {
        // PARENT
        char *msg = "Ini ditulis oleh PARENT\n";
        for (int i = 0; i < 5; i++) {
            write(fd, msg, strlen(msg));
        }
        wait(NULL); // tunggu child selesai
    }

    close(fd);
    return 0;
}