#include <sys/wait.h>

int status;
pid_t pid = wait(&status);

if (WIFEXITED(status)) {
    printf("Exited with code %d\n", WEXITSTATUS(status));
}
