#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void ask_and_delete(const char *filename) {
    char answer[10];
    printf("Видалити \"%s\"? (y/n/a/q): ", filename);
    fgets(answer, sizeof(answer), stdin);

    if (answer[0] == 'y' || answer[0] == 'Y') {
        if (remove(filename) == 0) {
            printf("✓ Видалено: %s\n", filename);
        } else {
            perror("remove");
        }
    } else if (answer[0] == 'a' || answer[0] == 'A') {
        if (remove(filename) == 0) {
            printf("✓ Видалено: %s\n", filename);
        }
        // Відразу видалимо все інше
        return;
    } else if (answer[0] == 'q' || answer[0] == 'Q') {
        printf("Вихід з програми.\n");
        exit(0);
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
            S_ISREG(st.st_mode)) {
            ask_and_delete(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
