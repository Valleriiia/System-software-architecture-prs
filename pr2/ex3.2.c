#include <stdio.h>

int main() {
    int i;
    printf("Top of the stack: %p\n", &i);

    // великий масив (~40 КБ)
    char big_stack1[40960];
    printf("After big_stack1: %p\n", &big_stack1);

    // ще один великий масив
    char big_stack2[40960];
    printf("After big_stack2: %p\n", &big_stack2);

    return 0;
}
