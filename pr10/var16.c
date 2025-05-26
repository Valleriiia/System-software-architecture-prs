#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == 0) {
        // Перший дочірній процес
        printf("Child 1 (PID: %d) is running\n", getpid());
        sleep(2);
        printf("Child 1 is exiting\n");
        exit(1);
    }

    pid2 = fork();

    if (pid2 == 0) {
        // Другий дочірній процес
        printf("Child 2 (PID: %d) is running\n", getpid());
        sleep(4);
        printf("Child 2 is exiting\n");
        exit(2);
    }

    // Батьківський процес
    int status;
    pid_t waited = waitpid(pid2, &status, 0);  // Чекає ТІЛЬКИ на pid2

    if (waited == pid2) {
        if (WIFEXITED(status)) {
            printf("Parent: Child 2 exited with code %d\n", WEXITSTATUS(status));
        }
    }

    // Дочекатися завершення іншого процесу, щоб уникнути зомбі
    wait(NULL); // для pid1

    return 0;
}
