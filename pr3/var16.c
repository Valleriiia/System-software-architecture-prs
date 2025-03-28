#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

void test_cpu_time() {
    struct rlimit limit;
    getrlimit(RLIMIT_CPU, &limit);
    printf("Max CPU time: %ld sec\n", limit.rlim_cur);
}

void test_file_size() {
    struct rlimit limit;
    getrlimit(RLIMIT_FSIZE, &limit);
    printf("Max file size: %ld blocks (512 bytes each)\n", limit.rlim_cur);
}

void test_stack_size() {
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    printf("Max stack size: %ld KB\n", limit.rlim_cur / 1024);
}

void test_open_files() {
    struct rlimit limit;
    getrlimit(RLIMIT_NOFILE, &limit);
    printf("Max open files: %ld\n", limit.rlim_cur);
}

int main() {
    printf("=== Testing ulimit settings ===\n");

    test_cpu_time();
    test_file_size();
    test_stack_size();
    test_open_files();

    printf("=== Test completed ===\n");
    return 0;
}
