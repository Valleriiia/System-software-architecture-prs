#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_TASKS 3

typedef struct {
    int interval_sec;
    char *command;
    timer_t timerid;
} CronTask;

CronTask tasks[MAX_TASKS];

void run_command(const char *cmd) {
    pid_t pid = fork();
    if (pid == 0) {
        // У дочірньому процесі
        execlp("/bin/sh", "sh", "-c", cmd, (char *)NULL);
        perror("execlp");
        exit(1);
    } else if (pid > 0) {
        // У батьківському — дочекаємось завершення
        waitpid(pid, NULL, 0);
    } else {
        perror("fork");
    }
}

void handler(int sig, siginfo_t *si, void *uc) {
    CronTask *task = si->si_value.sival_ptr;
    if (task && task->command) {
        printf("[cron] Running: %s\n", task->command);
        run_command(task->command);
    }
}

int main() {
    // Налаштування обробника сигналу
    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigaction(SIGRTMIN, &sa, NULL);

    // Створюємо завдання
    tasks[0] = (CronTask){5, "echo Hello every 5 sec"};
    tasks[1] = (CronTask){10, "date"};
    tasks[2] = (CronTask){15, "echo This runs every 15 sec"};

    for (int i = 0; i < MAX_TASKS; ++i) {
        struct sigevent sev = {0};
        sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo = SIGRTMIN;
        sev.sigev_value.sival_ptr = &tasks[i];

        if (timer_create(CLOCK_REALTIME, &sev, &tasks[i].timerid) == -1) {
            perror("timer_create");
            exit(1);
        }

        struct itimerspec its;
        its.it_value.tv_sec = tasks[i].interval_sec;
        its.it_value.tv_nsec = 0;
        its.it_interval.tv_sec = tasks[i].interval_sec;
        its.it_interval.tv_nsec = 0;

        if (timer_settime(tasks[i].timerid, 0, &its, NULL) == -1) {
            perror("timer_settime");
            exit(1);
        }

        printf("[cron] Scheduled: \"%s\" every %d sec\n",
               tasks[i].command, tasks[i].interval_sec);
    }

    // Блокуємо головний потік — чекаємо сигнали
    while (1) {
        pause();
    }

    return 0;
}
