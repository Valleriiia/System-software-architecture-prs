#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#define MAX_STACK_SIZE 256 * 1024  // 256 КБ

void set_stack_limit() {
    struct rlimit limit;
    limit.rlim_cur = MAX_STACK_SIZE;
    limit.rlim_max = MAX_STACK_SIZE;
    setrlimit(RLIMIT_STACK, &limit);
}

void recursive_function(int depth) {
    char arr[1024];  // Використовуємо пам’ять у стеку
    printf("Recursion depth: %d\n", depth);
    recursive_function(depth + 1);  // Рекурсивний виклик
}

int main() {
    set_stack_limit();
    recursive_function(1);
    return 0;
}
