#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **productions;
int num_productions;

int findProductionIndex(char symbol) {
    for (int i = 0; i < num_productions; i++) {
        if (productions[i][0] == symbol) {
            return i;
        }
    }
    return -1;
}

void findFirst(char symbol) {
    int index = findProductionIndex(symbol);
    if (index == -1) return;

    for (int i = 3; i < strlen(productions[index]); i++) {
        char current = productions[index][i];
        if ((current >= 'a' && current <= 'z') || current == ')' || current == '(' || current == ',') {
            printf(" %c ", current);
            break;
        } else if (current >= 'A' && current <= 'Z') {
            findFirst(current);
            break;
        } else if (current == '#') {
            printf(" # ");
            break;
        }
    }
}

void findFollow(char symbol) {
    if (symbol == 'S') {
        printf(" $ ");
    }

    for (int j = 0; j < num_productions; j++) {
        for (int i = 3; i < strlen(productions[j]); i++) {
            if (productions[j][i] == symbol) {
                char next = productions[j][i + 1];
                if ((next >= 'a' && next <= 'z') || next == ')' || next == '(' || next == ',') {
                    printf(" %c ", next);
                } else if (next >= 'A' && next <= 'Z') {
                    findFirst(next);
                } else if (i + 1 == strlen(productions[j])) {
                    findFollow(productions[j][0]);
                }
            }
        }
    }
}

int main() {
    printf("Enter the number of productions: ");
    scanf("%d", &num_productions);
    getchar();

    productions = (char**)malloc(num_productions * sizeof(char*));
    for (int i = 0; i < num_productions; i++) {
        productions[i] = (char*)malloc(20 * sizeof(char));
        printf("Enter production %d: ", i + 1);
        fgets(productions[i], 20, stdin);
        productions[i][strcspn(productions[i], "\n")] = 0;
    }

    for (int i = 0; i < num_productions; i++) {
        printf("\nFIRST(%c) = { ", productions[i][0]);
        findFirst(productions[i][0]);
        printf("}\n");
    }

    for (int i = 0; i < num_productions; i++) {
        printf("\nFOLLOW(%c) = { ", productions[i][0]);
        findFollow(productions[i][0]);
        printf("}\n");
    }

    for (int i = 0; i < num_productions; i++) {
        free(productions[i]);
    }
    free(productions);

    return 0;
}
