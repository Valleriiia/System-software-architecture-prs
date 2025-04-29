#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#define FILENAME "testfile.txt"
#define COPY_FILENAME "copied_testfile.txt"

int main() {
    FILE *fp;
    struct passwd *pw = getpwuid(getuid());
    if (!pw) {
        perror("Не вдалося отримати інформацію про користувача");
        return EXIT_FAILURE;
    }

    printf("Поточний користувач: %s\n", pw->pw_name);

    // 1. Створення файлу звичайним користувачем
    printf("\n[+] Створення файлу %s...\n", FILENAME);
    fp = fopen(FILENAME, "w");
    if (!fp) {
        perror("Не вдалося створити файл");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Це тестовий файл, створений звичайним користувачем.\n");
    fclose(fp);

    printf("[+] Файл створено.\n");

    // 2. Копіювання файлу як root (sudo)
    printf("\n[+] Копіювання файлу в домашню директорію через sudo...\n");

    char command[512];
    snprintf(command, sizeof(command), "sudo cp %s /home/%s/%s", FILENAME, pw->pw_name, COPY_FILENAME);
    if (system(command) != 0) {
        perror("Не вдалося скопіювати файл");
        return EXIT_FAILURE;
    }

    printf("[+] Файл скопійовано до /home/%s/%s\n", pw->pw_name, COPY_FILENAME);

    // 3. Спроба змінити файл звичайним користувачем
    printf("\n[+] Спроба змінити файл як звичайний користувач...\n");
    snprintf(command, sizeof(command), "/home/%s/%s", pw->pw_name, COPY_FILENAME);
    fp = fopen(command, "a");
    if (!fp) {
        perror("Не вдалося відкрити файл для запису");
        printf("[-] Ймовірно, відсутні права доступу для запису в файл.\n");
    } else {
        fprintf(fp, "Додано рядок від звичайного користувача.\n");
        fclose(fp);
        printf("[+] Запис успішний!\n");
    }

    // 4. Спроба видалити файл звичайним користувачем
    printf("\n[+] Спроба видалити файл як звичайний користувач...\n");
    if (remove(command) != 0) {
        perror("Не вдалося видалити файл");
        printf("[-] Ймовірно, відсутні права на видалення файлу.\n");
    } else {
        printf("[+] Файл успішно видалено!\n");
    }

    return 0;
}
