/*
 * Defect 3: Double free (Buggy version)
 * The same pointer returned by malloc() is passed to free()
 * twice. The second call operates on memory that has already
 * been released back to the allocator, corrupting heap metadata.
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
    /* ... later in the program, by mistake ... */
    free(msg);       /* BUG: double free on the same pointer */

    return 0;
}
