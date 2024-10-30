#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

int E(), Edash(), T(), Tdash(), F();
const char *cursor;
char string[64];

int main() {
    printf("Enter the string: ");
    scanf("%s", string);
    cursor = string;

    printf("\nInput Action\n");
    printf("----------------------------\n");

    if (E() && *cursor == '\0') {
        printf("----------------------------\n");
        printf("String is successfully parsed\n");
        return 0;
    }
    printf("----------------------------\n");
    printf("Error in parsing String\n");
    return 1;
}

int E() {
    printf("%-16s E -> T E'\n", cursor);
    return T() && Edash();
}

int Edash() {
    if (*cursor == '+') {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        return T() && Edash();
    }
    printf("%-16s E' -> $\n", cursor);
    return SUCCESS;
}

int T() {
    printf("%-16s T -> F T'\n", cursor);
    return F() && Tdash();
}

int Tdash() {
    if (*cursor == '*') {
        printf("%-16s T' -> * F T'\n", cursor);
        cursor++;
        return F() && Tdash();
    }
    printf("%-16s T' -> $\n", cursor);
    return SUCCESS;
}

int F() {
    if (*cursor == '(') {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E() && *cursor == ')') {
            cursor++;
            return SUCCESS;
        }
        return FAILED;
    } else if (strncmp(cursor, "id", 2) == 0) {
        printf("%-16s F -> id\n", cursor);
        cursor += 2;
        return SUCCESS;
    }
    return FAILED;
}
