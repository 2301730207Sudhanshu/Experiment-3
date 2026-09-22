/*
 * Defect 2: Memory leak (Buggy version)
 * Memory is allocated with malloc() inside a loop and the
 * pointer returned each time is never freed, so every
 * allocation is permanently lost once the loop iterates again.
 */
#include <stdio.h>
#include <stdlib.h>

void build_buffers(int count, int size) {
    for (int i = 0; i < count; i++) {
        int *buf = (int *)malloc(size * sizeof(int));  /* allocated */
        if (buf == NULL) {
            fprintf(stderr, "allocation failed\n");
            return;
        }
        for (int j = 0; j < size; j++) {
            buf[j] = i * size + j;
        }
        printf("Buffer %d first element = %d\n", i, buf[0]);
        /* BUG: 'buf' is never freed -> leaked on every iteration */
    }
}

int main(void) {
    build_buffers(5, 100);
    return 0;
}
