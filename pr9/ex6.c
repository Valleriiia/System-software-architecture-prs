#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void check_file(const char *path, const char *file) {
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, file);

    struct stat st;
    if (stat(fullpath, &st) == -1) {
        perror("Помилка stat");
        return;
    }

    printf("Файл: %s\n", fullpath);

    // Права доступу
    printf("  Права: ");
    printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // Доступ
    printf("  Доступність для користувача:\n");
    printf("    Читання: %s\n", (access(fullpath, R_OK) == 0) ? "ДОСТУПНО" : "ЗАБОРОНЕНО");
    printf("    Запис:   %s\n", (access(fullpath, W_OK) == 0) ? "ДОСТУПНО" : "ЗАБОРОНЕНО");
    printf("    Виконання: %s\n", (access(fullpath, X_OK) == 0) ? "ДОСТУПНО" : "ЗАБОРОНЕНО");
    printf("\n");
}

void check_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    printf("\n>>> Перевірка каталогу: %s\n", path);

    dir = opendir(path);
    if (!dir) {
        perror("Не вдалося відкрити каталог");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо "." і ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        check_file(path, entry->d_name);
    }

    closedir(dir);
}

int main() {
    check_directory(getenv("HOME"));    // Домашня директорія
    check_directory("/usr/bin");         // Системні бінарні файли
    check_directory("/etc");             // Конфігураційні файли

    return 0;
}
