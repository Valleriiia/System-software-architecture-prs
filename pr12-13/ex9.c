#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sigset_t set;
    siginfo_t info;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, NULL); // блокуємо SIGUSR1

    printf("Waiting for SIGUSR1...\n");
    sigwaitinfo(&set, &info);

    printf("Got signal %d from PID %d\n", info.si_signo, info.si_pid);
    return 0;
}
