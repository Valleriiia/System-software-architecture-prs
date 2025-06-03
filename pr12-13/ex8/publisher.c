#include <signal.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    pid_t pid = atoi(argv[1]);
    union sigval val;
    val.sival_int = 42;
    sigqueue(pid, SIGRTMIN, val);
}
