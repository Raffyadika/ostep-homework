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

        // waitpid() di child — tidak punya anak, langsung -1
        pid_t ret = waitpid(-1, NULL, 0);
        printf("Child: hasil waitpid() = %d\n", ret);

    } else {
        // PARENT
        printf("Parent: menunggu child PID = %d\n", pid);

        int status;
        pid_t ret = waitpid(pid, &status, 0);

        printf("Parent: waitpid() return = %d\n", ret);

        if (WIFEXITED(status)) {
            printf("Parent: child keluar normal, exit code = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}