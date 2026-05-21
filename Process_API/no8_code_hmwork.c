#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2]; // pipefd[0] = read end, pipefd[1] = write end

    if (pipe(pipefd) == -1) {
        printf("Pipe gagal!\n");
        return 1;
    }

    // ─────────────────────────────────────
    // CHILD 1 — Writer (stdout → pipe)
    // ─────────────────────────────────────
    pid_t child1 = fork();

    if (child1 == 0) {
        close(pipefd[0]); // child1 tidak perlu read end

        // Arahkan stdout ke write end pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // sudah diduplikasi, tutup aslinya

        printf("Halo dari Child 1!\n");
        printf("Pesan kedua dari Child 1!\n");

        return 0;
    }

    // ─────────────────────────────────────
    // CHILD 2 — Reader (pipe → stdin)
    // ─────────────────────────────────────
    pid_t child2 = fork();

    if (child2 == 0) {
        close(pipefd[1]); // child2 tidak perlu write end

        // Arahkan stdin ke read end pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // sudah diduplikasi, tutup aslinya

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Child 2 menerima: %s", buffer);
        }

        return 0;
    }

    // ─────────────────────────────────────
    // PARENT — tutup kedua end pipe, tunggu children
    // ─────────────────────────────────────
    close(pipefd[0]);
    close(pipefd[1]); // penting! supaya child2 tahu pipe sudah selesai

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    printf("Parent: semua child selesai\n");

    return 0;
}