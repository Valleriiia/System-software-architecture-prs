#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 12

// Структура для збереження слів з частотою
typedef struct {
    char keyword[50];
    int frequency;
} Word;

// Функції порівняння для qsort
int compare_by_keyword(const void *a, const void *b) {
    return strcmp(((Word *)a)->keyword, ((Word *)b)->keyword);
}

int compare_by_frequency(const void *a, const void *b) {
    return ((Word *)b)->frequency - ((Word *)a)->frequency;  // Спадний порядок
}

int compare_by_keyword_then_frequency(const void *a, const void *b) {
    int result = strcmp(((Word *)a)->keyword, ((Word *)b)->keyword);
    if (result == 0) { // Якщо ключові слова однакові, порівнюємо за частотою
        return ((Word *)b)->frequency - ((Word *)a)->frequency;
    }
    return result;
}

// Функція пошуку ВСІХ елементів за ключовим словом у відсортованій копії
void search_word_all(Word *array, int size, const char *key) {
    // Копіюємо масив і сортуємо його за keyword
    Word sorted_words[MAX_ITEMS];
    memcpy(sorted_words, array, sizeof(sorted_words));
    qsort(sorted_words, size, sizeof(Word), compare_by_keyword_then_frequency);

    // Виконуємо бінарний пошук у відсортованому масиві
    Word temp;
    strcpy(temp.keyword, key);
    
    Word *found = (Word *)bsearch(&temp, sorted_words, size, sizeof(Word), compare_by_keyword);
    
    if (!found) {
        printf("Слово '%s' не знайдено.\n", key);
        return;
    }

    // Знаходимо всі входження (ліворуч і праворуч)
    int index = found - sorted_words;
    int left = index, right = index;

    while (left > 0 && strcmp(sorted_words[left - 1].keyword, key) == 0) {
        left--;
    }
    
    while (right < size - 1 && strcmp(sorted_words[right + 1].keyword, key) == 0) {
        right++;
    }

    printf("Знайдено %d входжень слова '%s':\n", right - left + 1, key);
    for (int i = left; i <= right; i++) {
        printf("%s - %d\n", sorted_words[i].keyword, sorted_words[i].frequency);
    }
}

// Функція для безпечного введення числа з перевіркою
int get_valid_choice() {
    int choice;
    char buffer[50];
    while (1) {
        printf("\nВиберіть критерій сортування:\n");
        printf("1 - За keyword\n");
        printf("2 - За frequency\n");
        printf("3 - За keyword, а потім frequency\n");
        printf("Ваш вибір: ");
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &choice) == 1 && (choice == 1 || choice == 2 || choice == 3)) {
                return choice;
            }
        }
        printf("Помилка: введіть 1, 2 або 3.\n");
    }
}

int main() {
    Word words[MAX_ITEMS] = {
        {"kiwi", 9}, {"banana", 5}, {"apple", 10}, {"date", 3},
        {"cherry", 8}, {"grape", 15}, {"banana", 7}, {"apple", 12},
        {"elderberry", 12}, {"fig", 4}, {"honeydew", 6}, {"apple", 5}
    };

    // Вивід початкового (несортованого) списку
    printf("Початковий список слів:\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%s - %d\n", words[i].keyword, words[i].frequency);
    }

    // Вибір критерію сортування
    int choice = get_valid_choice();

    int (*comparator)(const void *, const void *);
    if (choice == 1) {
        comparator = compare_by_keyword;
    } else if (choice == 2) {
        comparator = compare_by_frequency;
    } else {
        comparator = compare_by_keyword_then_frequency;
    }

    // Сортування основного масиву
    qsort(words, MAX_ITEMS, sizeof(Word), comparator);

    // Вивід відсортованого списку
    printf("\nВідсортований список:\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%s - %d\n", words[i].keyword, words[i].frequency);
    }

    // Бінарний пошук усіх входжень
    char search_key[50];
    printf("\nВведіть слово для пошуку: ");
    scanf("%s", search_key);

    search_word_all(words, MAX_ITEMS, search_key);

    return 0;
}
