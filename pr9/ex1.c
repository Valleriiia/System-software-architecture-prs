#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define MIN_UID 1000  // Залежно від вашого дистрибутива: можливо 500 на старих системах

int main() {
    FILE *fp;
    char buffer[BUFFER_SIZE];

    // Виконуємо команду getent passwd
    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("Не вдалося виконати команду getent passwd");
        exit(EXIT_FAILURE);
    }

    printf("Звичайні користувачі на системі:\n");

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        char *username, *rest, *token;
        int uid;

        // Копіюємо рядок, бо strtok руйнує його
        char line_copy[BUFFER_SIZE];
        strncpy(line_copy, buffer, sizeof(line_copy));

        username = strtok(line_copy, ":");  // Ім'я користувача
        strtok(NULL, ":");                  // Пропустити поле пароля
        token = strtok(NULL, ":");           // UID

        if (token != NULL) {
            uid = atoi(token);
            if (uid >= MIN_UID && uid != getuid()) {
                printf("Користувач: %s (UID: %d)\n", username, uid);
            }
        }
    }

    pclose(fp);
    return 0;
}
