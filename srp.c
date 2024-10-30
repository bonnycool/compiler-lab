#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[50], input[50];
int top = -1, inputIndex = 0;

void push(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        stack[++top] = str[i];
    }
    stack[top + 1] = '\0';
}

void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

void printState() {
    printf("$%s\t%s$\t", stack, &input[inputIndex]);
}

void checkReduction() {
    // Repeat reduction until no further reduction is possible
    while (1) {
        // Reduction rules for S -> S+S or S -> S*S
        if (top >= 2 && stack[top - 2] == 'S' &&
            (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'S') {
            printState();
            printf("REDUCE TO S -> S%cS\n", stack[top - 1]);
            pop(3);
            push("S");
        }
        // Reduction rule for S -> id
        else if (top >= 1 && strcmp(stack + top - 1, "id") == 0) {
            printState();
            printf("REDUCE TO S -> id\n");
            pop(2);
            push("S");
        } else {
            break; // No further reduction possible
        }
    }
}

int main() {
    printf("GRAMMAR is -\nS->S+S\nS->S*S\nS->id\n");
    printf("\nEnter input string: ");
    scanf("%s", input);

    printf("\nstack\t input \t\t action\n");

    while (1) {
        printState();

        // Shift operation for "id"
        if (strncmp(&input[inputIndex], "id", 2) == 0) {
            printf("SHIFT id\n");
            push("id");
            inputIndex += 2;
        }
        // Shift operation for operators "+" and "*"
        else if (input[inputIndex] == '+' || input[inputIndex] == '*') {
            printf("SHIFT %c\n", input[inputIndex]);
            char op[2] = {input[inputIndex], '\0'};
            push(op);
            inputIndex++;
        }
        // Check for end of input
        else if (input[inputIndex] == '\0') {
            checkReduction();
            if (strcmp(stack, "S") == 0) {
                printf("Accept\n");
                break;
            } else {
                printf("Reject\n");
                break;
            }
        } else {
            printf("Invalid input\n");
            break;
        }

        // Perform reduction after each shift
        checkReduction();
    }

    return 0;
}
