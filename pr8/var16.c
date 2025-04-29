// task8_5.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define FILENAME "race_file.txt"

void write_data(const char *text) {
    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (int i = 0; i < 1000; i++) {
        if (write(fd, text, 1) < 0) {
            perror("write");
            close(fd);
            exit(1);
        }
    }

    close(fd);
}

int main() {
    // Створити або очистити файл перед початком
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd >= 0) close(fd);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        // Дочірній процес
        write_data("C");
    }
    else {
        // Батьківський процес
        write_data("P");

        wait(NULL); // Чекати завершення дитини
    }

    printf("Finished writing to %s\n", FILENAME);

    return 0;
}
