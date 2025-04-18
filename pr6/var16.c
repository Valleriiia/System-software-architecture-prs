#include <stdio.h>

int main() {
    char buffer[10];  // масив з фіксованим розміром 10 байт

    // Наміром виходимо за межі масиву
    for (int i = 0; i <= 10; i++) {
        buffer[i] = 'A' + i;
    }

    // Вивід масиву (може бути некоректним через overflow)
    for (int i = 0; i <= 10; i++) {
        printf("%c ", buffer[i]);
    }

    printf("\n");
    return 0;
}
