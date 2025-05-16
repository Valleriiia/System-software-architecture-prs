#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[1024];

    // Виконуємо команду rwho
    fp = popen("rwho", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // Відкриваємо канал для передачі виводу в more
    FILE *more = popen("more", "w");
    if (more == NULL) {
        perror("popen for more failed");
        pclose(fp);
        return 1;
    }

    // Передаємо вивід rwho у more
    while (fgets(buffer, sizeof(buffer), fp)) {
        fputs(buffer, more);
    }

    pclose(fp);
    pclose(more);
    return 0;
}
