/*
 * dirty_code.c
 * Deliberately "dirty" version of a simple user-record processing program.
 * Used as the BEFORE snippet for the dirty-code analysis experiment.
 *
 * Contains (intentionally): magic numbers, dead code, unchecked return
 * values, unsafe string functions, deeply nested logic and a suppressed
 * compiler warning.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char name[20];
    char password[20];
    int  age;
    int  role;
};

int global_count = 0;   /* unused after refactor, kept to show dead state */

/* --------------------------------------------------------------------- */
void copy_name(char *dest, char *src)
{
    strcpy(dest, src);              /* DIRTY: unsafe string function */
}

/* --------------------------------------------------------------------- */
int read_password(struct user *u)
{
    printf("Enter password: ");
    gets(u->password);              /* DIRTY: unsafe, no bounds checking */
    return 1;
}

/* --------------------------------------------------------------------- */
void grant_access(struct user *u, int level)
{
    /* DIRTY: deeply nested logic (arrow / pyramid code) */
    if (u != NULL) {
        if (u->age > 0) {
            if (u->age < 150) {
                if (level >= 0) {
                    if (level <= 5) {
                        if (u->role == 1) {
                            if (level > 3) {
                                printf("Admin access granted at level %d\n", level);
                            } else {
                                printf("Limited admin access\n");
                            }
                        } else {
                            printf("User access granted\n");
                        }
                    }
                }
            }
        }
    }
    return;

    printf("This line can never run\n");   /* DIRTY: dead code */
}

/* --------------------------------------------------------------------- */
int process_record(char *name_in, char *pass_in, int age)
{
    struct user u;
    char buffer[10];

#pragma GCC diagnostic ignored "-Wunused-variable"   /* DIRTY: suppressed warning */
    int unused_flag = 42;

    copy_name(u.name, name_in);
    strcpy(u.password, pass_in);     /* DIRTY: unsafe function, no length check */

    sprintf(buffer, "%s", name_in);  /* DIRTY: unsafe, buffer[10] can overflow */

    u.age = age;

    if (age > 18) {                  /* DIRTY: magic number, meaning unclear */
        u.role = 1;
    } else {
        u.role = 0;
    }

    FILE *fp = fopen("users.log", "a");
    fprintf(fp, "%s logged\n", u.name);   /* DIRTY: unchecked return value of fopen (fp may be NULL) */
    fclose(fp);

    int *data = malloc(100);         /* DIRTY: magic number, unchecked malloc return */
    data[0] = age * 3600 * 24 * 30;  /* DIRTY: magic numbers, possible NULL deref */
    free(data);

    global_count = global_count + 1;

    grant_access(&u, 4);

    return 0;
}

/* --------------------------------------------------------------------- */
int main(void)
{
    char name[20];
    char pass[20];

    printf("Enter name: ");
    scanf("%s", name);               /* DIRTY: unchecked return value of scanf */

    struct user u;
    read_password(&u);

    process_record(name, u.password, 25);

    return 0;
}
