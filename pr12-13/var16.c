#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void print_pending_signals() {
    sigset_t pending;
    sigpending(&pending);

    printf("[*] Pending signals: ");
    for (int i = 1; i < NSIG; ++i) {
        if (sigismember(&pending, i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    sigset_t set;
    siginfo_t info;

    // Сигнали, які будемо блокувати й чекати
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);

    // Блокуємо SIGUSR1 і SIGUSR2
    if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) {
        perror("sigprocmask");
        return 1;
    }

    printf("[*] PID: %d\n", getpid());
    printf("[*] Send SIGUSR1 or SIGUSR2 from another terminal (kill -USR1 %d)\n", getpid());

    // Затримка, щоб дати час на відправку сигналів
    sleep(5);

    // Виводимо, які сигнали доставлено, але ще не оброблено
    print_pending_signals();

    // Встановимо обробник (не викликається тут, бо ми використовуємо sigwaitinfo)
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN; // Не потрібен, але обов'язково треба задати щось
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // Синхронно чекаємо сигнал
    printf("[*] Waiting for signal using sigwaitinfo...\n");
    if (sigwaitinfo(&set, &info) > 0) {
        printf("[+] Received signal %d from PID %d\n", info.si_signo, info.si_pid);
    } else {
        perror("sigwaitinfo");
    }

    return 0;
}
