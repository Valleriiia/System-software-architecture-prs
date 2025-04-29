// task8_3.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Функція порівняння для qsort
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

// Функція для вимірювання часу сортування
double measure_sort_time(int *array, size_t size) {
    int *copy = malloc(size * sizeof(int));
    memcpy(copy, array, size * sizeof(int));

    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare_ints);
    clock_t end = clock();

    free(copy);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Функції генерації масивів
void generate_sorted(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = i;
    }
}

void generate_reversed(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = size - i;
    }
}

void generate_random(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = rand();
    }
}

void generate_constant(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = 42;
    }
}

int is_sorted(int *array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (array[i-1] > array[i]) return 0;
    }
    return 1;
}

void run_test(int *array, size_t size, const char *test_name) {
    qsort(array, size, sizeof(int), compare_ints);
    if (is_sorted(array, size)) {
        printf("Тест \"%s\": успіх\n", test_name);
    } else {
        printf("Тест \"%s\": помилка\n", test_name);
    }
}


int main() {
    srand(time(NULL));

    const size_t size = 10000;
    int *array = malloc(size * sizeof(int));

    run_test(array, size, "Тест1");

    printf("Аналіз швидкості qsort:\n");

    generate_sorted(array, size);
    printf("Вже відсортований масив: %f секунд\n", measure_sort_time(array, size));

    generate_reversed(array, size);
    printf("Обернено відсортований масив: %f секунд\n", measure_sort_time(array, size));

    generate_random(array, size);
    printf("Випадковий масив: %f секунд\n", measure_sort_time(array, size));

    generate_constant(array, size);
    printf("Масив із однаковими значеннями: %f секунд\n", measure_sort_time(array, size));

    free(array);
    return 0;
}
