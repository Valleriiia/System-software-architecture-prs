#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t huge_size = (size_t)-1; // Великий розмір, що має провалити виділення
    void *ptr = malloc(16); // Спочатку виділяємо невеликий блок

    if (!ptr) {
        printf("Initial malloc failed\n");
        return 1;
    }

    printf("Initial allocation successful: %p\n", ptr);

    // Спроба розширити пам'ять до нереального розміру
    void *new_ptr = realloc(ptr, huge_size);
    
    if (new_ptr == NULL) {
        printf("realloc failed, original pointer is still valid: %p\n", ptr);
        free(ptr); // Не забуваємо звільнити пам’ять!
    } else {
        printf("Unexpected success: %p\n", new_ptr);
        free(new_ptr);
    }

    return 0;
}
