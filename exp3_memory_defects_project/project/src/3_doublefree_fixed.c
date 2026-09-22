/*
 * Defect 3: Double free (Fixed version)
 * FIX: after the first free(), the pointer is set to NULL.
 * free(NULL) is well-defined and does nothing, so an accidental
 * second call can no longer corrupt the heap.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *msg = (char *)malloc(32);
    if (msg == NULL) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }
    strcpy(msg, "hello valgrind");
    printf("%s\n", msg);

    free(msg);       /* first, legitimate free */
    msg = NULL;       /* FIX: avoid dangling pointer */

    free(msg);        /* safe no-op: free(NULL) is well-defined */

    return 0;
}
