#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("[+] Виконуємо команду whoami:\n");
    if (system("whoami") != 0) {
        perror("Помилка виконання whoami");
    }

    printf("\n[+] Виконуємо команду id:\n");
    if (system("id") != 0) {
        perror("Помилка виконання id");
    }

    printf("\n[+] Програма завершена успішно.\n");

    return 0;
}
