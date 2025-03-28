#include <stdio.h>
#include <stdlib.h>

int global_initialized = 1;         // .data
int global_uninitialized;           // .bss

void print_segments();

int main() {
    int local_var = 42;             // стек
    int *heap_var = malloc(sizeof(int)); // купа
    *heap_var = 99;

    printf("=== Address locations ===\n");
    printf("Code (text):        %p\n", print_segments);
    printf("Global init (.data):  %p\n", &global_initialized);
    printf("Global uninit (.bss): %p\n", &global_uninitialized);
    printf("Heap:               %p\n", heap_var);
    printf("Stack:              %p\n", &local_var);

    free(heap_var);
    return 0;
}

void print_segments() {}  // функція для .text
