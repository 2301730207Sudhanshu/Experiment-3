/*
 * clean_code.c
 * Refactored, standards-compliant version of dirty_code.c
 *
 * Fixes applied (see lab report findings table for full mapping):
 *   - Named constants instead of magic numbers
 *   - No dead/unreachable code
 *   - All return values checked (malloc, fopen, fgets, snprintf)
 *   - No unsafe string functions (strcpy/gets/sprintf) -> strncpy/snprintf/fgets
 *   - Nested logic flattened using guard clauses (early return) and helper
 *     functions -> max nesting depth kept <= 3 (MISRA C:2012 Rule 15.4 spirit)
 *   - No suppressed compiler warnings; unused variable removed instead
 *   - Bounds-checked buffers, sizes derived with sizeof()
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX_LEN        20
#define PASSWORD_MAX_LEN     20
#define ADULT_AGE_THRESHOLD  18
#define MIN_VALID_AGE         1
#define MAX_VALID_AGE        150
#define MIN_ACCESS_LEVEL      0
#define MAX_ACCESS_LEVEL      5
#define ADMIN_LEVEL_THRESHOLD  3
#define ROLE_ADMIN             1
#define ROLE_USER               0
#define SECONDS_PER_DAY        86400  /* 3600 * 24, named instead of magic */
#define DAYS_PER_MONTH          30
#define DATA_BUFFER_ELEMENTS    25    /* replaces malloc(100) magic number
                                          (25 * sizeof(int) = 100 bytes)   */
#define LOG_FILE_NAME       "users.log"

struct user {
    char name[NAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];
    int  age;
    int  role;
};

/* --------------------------------------------------------------------- */
/* Safe, bounded string copy. Always NUL-terminates dest.                */
static void safe_copy(char *dest, size_t dest_size, const char *src)
{
    if ((dest == NULL) || (src == NULL) || (dest_size == 0U)) {
        return;
    }
    strncpy(dest, src, dest_size - 1U);
    dest[dest_size - 1U] = '\0';
}

/* --------------------------------------------------------------------- */
/* Safe replacement for gets(): bounded, checks return value.            */
static int read_password(struct user *u)
{
    if (u == NULL) {
        return 0;
    }

    printf("Enter password: ");
    if (fgets(u->password, (int)sizeof(u->password), stdin) == NULL) {
        return 0;
    }

    /* strip trailing newline left by fgets, if present */
    size_t len = strlen(u->password);
    if ((len > 0U) && (u->password[len - 1U] == '\n')) {
        u->password[len - 1U] = '\0';
    }
    return 1;
}

/* --------------------------------------------------------------------- */
/* Flattened access-decision logic using guard clauses (no pyramid).     */
static void grant_access(const struct user *u, int level)
{
    if (u == NULL) {
        return;
    }
    if ((u->age < MIN_VALID_AGE) || (u->age > MAX_VALID_AGE)) {
        return;
    }
    if ((level < MIN_ACCESS_LEVEL) || (level > MAX_ACCESS_LEVEL)) {
        return;
    }

    if (u->role != ROLE_ADMIN) {
        printf("User access granted\n");
        return;
    }

    if (level > ADMIN_LEVEL_THRESHOLD) {
        printf("Admin access granted at level %d\n", level);
    } else {
        printf("Limited admin access\n");
    }
}

/* --------------------------------------------------------------------- */
/* Appends a login line to the log file. Returns 0 on success.           */
static int write_log_entry(const char *name)
{
    FILE *fp = fopen(LOG_FILE_NAME, "a");
    if (fp == NULL) {
        perror("fopen(users.log) failed");
        return -1;
    }

    if (fprintf(fp, "%s logged\n", name) < 0) {
        (void)fclose(fp);
        return -1;
    }

    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

/* --------------------------------------------------------------------- */
static int process_record(const char *name_in, const char *pass_in, int age)
{
    struct user u;

    if ((name_in == NULL) || (pass_in == NULL)) {
        return -1;
    }

    safe_copy(u.name, sizeof(u.name), name_in);
    safe_copy(u.password, sizeof(u.password), pass_in);

    u.age  = age;
    u.role = (age > ADULT_AGE_THRESHOLD) ? ROLE_ADMIN : ROLE_USER;

    if (write_log_entry(u.name) != 0) {
        fprintf(stderr, "Warning: could not write log entry\n");
        /* not fatal to the rest of the flow, continue */
    }

    int *data = malloc(DATA_BUFFER_ELEMENTS * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        return -1;
    }
    data[0] = age * SECONDS_PER_DAY * DAYS_PER_MONTH;
    free(data);
    data = NULL;

    grant_access(&u, ADMIN_LEVEL_THRESHOLD + 1);

    return 0;
}

/* --------------------------------------------------------------------- */
int main(void)
{
    char name[NAME_MAX_LEN];
    struct user u;

    printf("Enter name: ");
    if (scanf("%19s", name) != 1) {
        fprintf(stderr, "Error: failed to read name\n");
        return EXIT_FAILURE;
    }

    if (read_password(&u) == 0) {
        fprintf(stderr, "Error: failed to read password\n");
        return EXIT_FAILURE;
    }

    if (process_record(name, u.password, 25) != 0) {
        fprintf(stderr, "Error: failed to process record\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
