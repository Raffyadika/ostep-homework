#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Argumen untuk execv, execvp, execvpe
    char *args[] = {"ls", "-l", NULL};

    // Environment untuk execle, execvpe
    char *env[] = {"PATH=/bin", NULL};

    // ─────────────────────────────────────
    // 1. execl() — argumen list, path lengkap
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execl ===\n");
        execl("/bin/ls", "ls", "-l", NULL);
    }
    wait(NULL);

    // ─────────────────────────────────────
    // 2. execle() — argumen list, path lengkap, custom env
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execle ===\n");
        execle("/bin/ls", "ls", "-l", NULL, env);
    }
    wait(NULL);

    // ─────────────────────────────────────
    // 3. execlp() — argumen list, cari di $PATH
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execlp ===\n");
        execlp("ls", "ls", "-l", NULL);
    }
    wait(NULL);

    // ─────────────────────────────────────
    // 4. execv() — argumen array, path lengkap
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execv ===\n");
        execv("/bin/ls", args);
    }
    wait(NULL);

    // ─────────────────────────────────────
    // 5. execvp() — argumen array, cari di $PATH
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execvp ===\n");
        execvp("ls", args);
    }
    wait(NULL);

    // ─────────────────────────────────────
    // 6. execvpe() — argumen array, cari di $PATH, custom env
    // ─────────────────────────────────────
    pid = fork();
    if (pid == 0) {
        printf("\n=== execvpe ===\n");
        execvpe("ls", args, env);
    }
    wait(NULL);

    return 0;
}