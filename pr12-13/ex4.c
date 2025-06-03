#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;   
    sa.sa_flags = SA_NOCLDWAIT;     
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);  

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Дочірній процес
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(0);
    } else {
        // Батьківський процес
        printf("Parent (PID: %d), spawned child PID: %d\n", getpid(), pid);
        sleep(5);  // дочекатись завершення дочірнього
        printf("Parent exiting.\n");
    }

    return 0;
}
