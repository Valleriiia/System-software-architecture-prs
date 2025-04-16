#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Data {
    char a;
    double d;
};

int main() {
    struct Data source = {'A', 3.14159};

    // Виділяємо буфер пам’яті з неправильним вирівнюванням
    char *buffer = malloc(sizeof(struct Data) + 1);
    if (!buffer) {
        perror("malloc");
        return 1;
    }

    // Зсуваємо адресу на 1 байт => вирівнювання порушено
    void *unaligned_ptr = buffer + 1;

    // Копіюємо структуру в неправильно вирівняну адресу
    memcpy(unaligned_ptr, &source, sizeof(struct Data));

    // Спроба прочитати значення через приведення типу — UB (undefined behavior)
    struct Data *dest = (struct Data *)unaligned_ptr;

    // Може призвести до крашу або некоректних даних
    printf("a = %c\n", dest->a);
    printf("d = %f\n", dest->d);  // <-- потенційно аварійне завершення

    free(buffer);
    return 0;
}
