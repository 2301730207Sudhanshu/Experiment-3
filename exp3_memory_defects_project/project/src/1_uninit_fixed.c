/*
 * Defect 1: Initialization error (Fixed version)
 * FIX: 'flag' is explicitly initialised before use, removing the
 * dependency on an indeterminate stack value.
 */
#include <stdio.h>

int decide(void) {
    int flag = 0;          /* FIX: explicitly initialised */
    int result;

    if (flag) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int main(void) {
    int outcome = decide();
    printf("Outcome = %d\n", outcome);
    return 0;
}
