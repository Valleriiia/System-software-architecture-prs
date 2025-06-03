#include <time.h>
#include <stdio.h>
#include <errno.h>

int main() {
    struct timespec req = {1, 0}; // 1 сек
    while (nanosleep(&req, &req) == -1 && errno == EINTR) {
        printf("Interrupted by signal, resuming sleep...\n");
    }
    printf("Finished sleep\n");
    return 0;
}
