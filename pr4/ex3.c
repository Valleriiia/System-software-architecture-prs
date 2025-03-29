#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0); // Виділення 0 байтів

    if (ptr == NULL) {
        printf("malloc(0) returned NULL\n");
    } else {
        printf("malloc(0) returned a non-NULL pointer: %p\n", ptr);
    }

    free(ptr); // Повинно бути безпечним
    return 0;
}
