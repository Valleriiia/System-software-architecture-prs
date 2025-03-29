#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 10

typedef struct sbar {
    int data;
} sbar;

typedef struct MemoryPool {
    sbar pool[POOL_SIZE];   // Місце для об'єктів
    int free_slots[POOL_SIZE]; // Індикатор зайнятості слотів
} MemoryPool;

void init_pool(MemoryPool *mp) {
    memset(mp->free_slots, 1, sizeof(mp->free_slots)); // 1 означає "вільний"
}

sbar* allocate_from_pool(MemoryPool *mp) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (mp->free_slots[i]) {
            mp->free_slots[i] = 0; // Позначаємо як зайнятий
            return &mp->pool[i];
        }
    }
    return NULL; // Немає вільних слотів
}

void free_to_pool(MemoryPool *mp, sbar *ptr) {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (&mp->pool[i] == ptr) {
            mp->free_slots[i] = 1; // Позначаємо як вільний
            return;
        }
    }
}

int main() {
    MemoryPool mp;
    init_pool(&mp);

    sbar *obj1 = allocate_from_pool(&mp);
    sbar *obj2 = allocate_from_pool(&mp);

    if (obj1) obj1->data = 42;
    if (obj2) obj2->data = 99;

    printf("obj1->data: %d\n", obj1 ? obj1->data : -1);
    printf("obj2->data: %d\n", obj2 ? obj2->data : -1);

    free_to_pool(&mp, obj1);
    free_to_pool(&mp, obj2);

    return 0;
}
