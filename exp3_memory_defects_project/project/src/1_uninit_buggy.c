/*
 * Defect 1: Initialization error (Buggy version)
 * A local variable 'flag' is declared but never initialized.
 * Its value is then used in a conditional branch, which is
 * undefined behaviour and will be flagged by Valgrind/ASan as
 * a use of an uninitialised value.
 */
#include <stdio.h>

int decide(void) {
    int flag;              /* NOT initialised */
    int result;

    if (flag) {            /* BUG: branch depends on uninitialised value */
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
