#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    return (lenstr >= lensuffix) && (strcmp(str + lenstr - lensuffix, suffix) == 0);
}

void ask_and_set_permission(const char *filename) {
    char answer[10];
    printf("Надати іншим дозвіл на читання для \"%s\"? (y/n): ", filename);
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == 'y' || answer[0] == 'Y') {
        struct stat st;
        if (stat(filename, &st) == 0) {
            mode_t new_mode = st.st_mode | S_IROTH;
            if (chmod(filename, new_mode) == 0) {
                printf("✓ Дозвіл на читання надано: %s\n", filename);
            } else {
                perror("chmod");
            }
        } else {
            perror("stat");
        }
    }
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &st) == 0 &&
            S_ISREG(st.st_mode) &&
            access(entry->d_name, X_OK) == 0 &&
            !ends_with(entry->d_name, ".c")) {
            ask_and_set_permission(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
