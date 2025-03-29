#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int xa = 100000;
    int xb = 100000;

    // Переповнення зі знаком
    int num_signed = xa * xb;
    size_t num_unsigned = (size_t)num_signed;  // Конвертуємо в size_t

    printf("num_signed: %d\n", num_signed);
    printf("num_unsigned: %zu\n", num_unsigned);

    void *ptr = malloc(num_unsigned);
    if (ptr == NULL) {
        printf("malloc failed!\n");
    } else {
        printf("malloc succeeded!\n");
        free(ptr);
    }

    return 0;
}
