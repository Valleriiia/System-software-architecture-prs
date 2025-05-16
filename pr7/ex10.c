#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float random_float_0_1() {
    return (float) rand() / (float) RAND_MAX;
}

float random_float_0_n(float n) {
    return random_float_0_1() * n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <дійсне_число_n>\n", argv[0]);
        return 1;
    }

    float n = atof(argv[1]);

    // Унікальна ініціалізація генератора
    srand((unsigned int) time(NULL));

    printf("5 випадкових чисел у [0.0; 1.0]:\n");
    for (int i = 0; i < 5; i++) {
        printf("%f\n", random_float_0_1());
    }

    printf("\n5 випадкових чисел у [0.0; %f]:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("%f\n", random_float_0_n(n));
    }

    return 0;
}
