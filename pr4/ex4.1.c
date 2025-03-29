#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    int i = 0;
    
    while (i < 5) { // 5 ітерацій для тесту
        if (!ptr)
            ptr = malloc(16); // Виділяємо 16 байтів

        printf("Iteration %d, ptr: %p\n", i, ptr);

        free(ptr); // Звільняємо пам'ять, але ptr все ще зберігає її адресу!

        i++;
    }

    return 0;
}
