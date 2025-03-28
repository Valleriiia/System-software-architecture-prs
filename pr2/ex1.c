#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    time_t max_time;

    if ((time_t)-1 > 0) {
        // time_t is unsigned
        max_time = (time_t)~0;
    } else {
        // time_t is signed
        max_time = (time_t)((1ULL << (sizeof(time_t) * 8 - 1)) - 1);
    }

    printf("Максимальне значення time_t: %lld\n", (long long)max_time);

    struct tm *tm_time = gmtime(&max_time);
    if (tm_time) {
        printf("Цей момент часу: %s", asctime(tm_time));
    } else {
        perror("Помилка перетворення часу");
    }

    return 0;
}
