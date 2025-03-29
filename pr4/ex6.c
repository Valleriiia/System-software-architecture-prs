#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;

    // realloc з NULL -> має поводитися як malloc
    ptr = realloc(NULL, 16);
    printf("realloc(NULL, 16): %p\n", ptr);

    if (ptr) free(ptr);

    // realloc з 0 -> має поводитися як free
    ptr = malloc(16);
    printf("Allocated memory: %p\n", ptr);

    void *new_ptr = realloc(ptr, 0);
    printf("realloc(ptr, 0): %p\n", new_ptr);

    if (new_ptr) free(new_ptr);

    return 0;
}
