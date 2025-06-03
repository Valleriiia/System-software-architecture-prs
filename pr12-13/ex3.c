#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

    // Блокуємо SIGINT
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT is now blocked. PID: %d\n", getpid());
    while (1) {
        sleep(1);
    }
    return 0;
}
