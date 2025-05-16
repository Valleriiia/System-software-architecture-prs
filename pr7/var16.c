#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/fs.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Використання: %s <файл>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("fstat");
        close(fd);
        return 1;
    }

    int block_size;
    if (ioctl(fd, FIGETBSZ, &block_size) < 0) {
        perror("ioctl FIGETBSZ");
        close(fd);
        return 1;
    }

    int num_blocks = (st.st_size + block_size - 1) / block_size;
    int fragments = 0;
    int prev_block = -1;

    for (int i = 0; i < num_blocks; i++) {
        int logical = i;
        if (ioctl(fd, FIBMAP, &logical) < 0) {
            perror("ioctl FIBMAP");
            close(fd);
            return 1;
        }

        if (logical == 0)
            continue;  // пропускаємо «дірки» в sparse файлах

        if (prev_block == -1 || logical != prev_block + 1) {
            fragments++;
        }
        prev_block = logical;
    }

    close(fd);

    printf("Розмір файлу: %ld байт\n", st.st_size);
    printf("Блоків: %d\n", num_blocks);
    printf("Фрагментів: %d\n", fragments);
    printf("Рівень фрагментації: %.2f%%\n", (100.0 * fragments / num_blocks));

    return 0;
}
