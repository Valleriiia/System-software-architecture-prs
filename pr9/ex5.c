#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TEMP_FILE "tempfile.txt"

int main() {
    FILE *fp;
    printf("[+] Створення тимчасового файлу від імені звичайного користувача...\n");

    // 1. Створення файлу
    fp = fopen(TEMP_FILE, "w");
    if (!fp) {
        perror("Не вдалося створити тимчасовий файл");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Тимчасовий файл для тесту.\n");
    fclose(fp);

    printf("[+] Тимчасовий файл створено: %s\n", TEMP_FILE);

    // 2. Зміна власника та прав доступу через sudo
    printf("[+] Зміна власника на root та прав доступу (chmod 600)...\n");

    if (system("sudo chown root:root tempfile.txt") != 0) {
        perror("Помилка виконання chown");
    }
    if (system("sudo chmod 600 tempfile.txt") != 0) {
        perror("Помилка виконання chmod");
    }

    // 3. Перевірка можливості читати і писати файл
    printf("\n[+] Перевірка прав доступу користувача до файлу...\n");

    if (access(TEMP_FILE, R_OK) == 0) {
        printf("[*] Користувач МОЖЕ читати файл.\n");
    } else {
        printf("[*] Користувач НЕ МОЖЕ читати файл.\n");
    }

    if (access(TEMP_FILE, W_OK) == 0) {
        printf("[*] Користувач МОЖЕ записувати у файл.\n");
    } else {
        printf("[*] Користувач НЕ МОЖЕ записувати у файл.\n");
    }

    return 0;
}
