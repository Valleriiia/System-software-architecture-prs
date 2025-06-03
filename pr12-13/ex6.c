#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>

void handler(int sig, siginfo_t *info, void *context) {
    ucontext_t *uc = (ucontext_t *)context;
#if defined(__x86_64__)
    printf("RIP: %llx\n", (unsigned long long)uc->uc_mcontext.gregs[REG_RIP]);
#endif
    exit(1);
}

int main() {
    struct sigaction sa = {0};
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    *p = 1; // викликає SIGSEGV
    return 0;
}
