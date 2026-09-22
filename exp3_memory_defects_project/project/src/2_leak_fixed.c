/*
 * Defect 2: Memory leak (Fixed version)
 * FIX: each buffer is freed once it is no longer needed,
 * so no allocation escapes the loop unreleased.
 */
#include <stdio.h>
#include <stdlib.h>

void build_buffers(int count, int size) {
    for (int i = 0; i < count; i++) {
        int *buf = (int *)malloc(size * sizeof(int));
        if (buf == NULL) {
            fprintf(stderr, "allocation failed\n");
            return;
        }
        for (int j = 0; j < size; j++) {
            buf[j] = i * size + j;
        }
        printf("Buffer %d first element = %d\n", i, buf[0]);
        free(buf);          /* FIX: release memory after use */
        buf = NULL;
    }
}

int main(void) {
    build_buffers(5, 100);
    return 0;
}
