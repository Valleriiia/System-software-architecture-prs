#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char buffer[65536]; // 64 KB
    memset(buffer, 'A', sizeof(buffer));

    // Закриємо читання, щоб швидше викликати обмеження буфера
    close(pipefd[0]);

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count == -1) {
        perror("write");
    } else {
        printf("Запитували записати %lu байт, фактично записано %zd байт\n", sizeof(buffer), count);
    }

    close(pipefd[1]);
    return 0;
}
