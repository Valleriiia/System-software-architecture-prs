#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef int (*func_t)(void);

int main() {
    // Машинний код функції: return 42
    unsigned char code1[] = {
        0xB8, 0x2A, 0x00, 0x00, 0x00, // mov eax, 42
        0xC3                          // ret
    };

    size_t pagesize = sysconf(_SC_PAGESIZE);
    void *mem = mmap(NULL, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    memcpy(mem, code1, sizeof(code1));
    func_t f = (func_t)mem;

    printf("First function returns: %d\n", f());

    // Змінюємо розмір (вдвічі більше) за допомогою mremap
    void *mem2 = mremap(mem, pagesize, pagesize * 2, MREMAP_MAYMOVE);
    if (mem2 == MAP_FAILED) {
        perror("mremap");
        return 1;
    }

    // Додаємо другу функцію після першої: return 99
    unsigned char code2[] = {
        0xB8, 0x63, 0x00, 0x00, 0x00, // mov eax, 99
        0xC3                          // ret
    };

    memcpy(mem2 + sizeof(code1), code2, sizeof(code2));
    func_t g = (func_t)(mem2 + sizeof(code1));

    printf("Second function returns: %d\n", g());

    munmap(mem2, pagesize * 2);
    return 0;
}
