#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[33][10] = { 
    "auto","break","case","char","const","continue",
    "default","do","double","else","enum","extern",
    "float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct",
    "switch","typedef","union","unsigned","void","volatile","while", "main"
};

int isKeyword(char *token) {
    for (int i = 0; i < 33; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char *token) {
    char operators[15][3] = {"+", "-", "*", "/", "%", "=", "==", "<", ">", "!", "<=", ">=", "!=", "&&", "||"};
    for (int i = 0; i < 15; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isNumber(char *token) {
    for (int i = 0; i < strlen(token); i++) {
        if (!isdigit(token[i])) {
            return 0;
        }
    }
    return 1;
}

int isIdentifier(char *token) {
    // Check if it's a valid identifier (starts with a letter or underscore, then only letters, digits, or underscores)
    if (isalpha(token[0]) || token[0] == '_') {
        for (int i = 1; i < strlen(token); i++) {
            if (!isalnum(token[i]) && token[i] != '_') {
                return 0; // Invalid if it contains invalid characters
            }
        }
        return 1;
    }
    return 0;
}

int isInvalidIdentifier(char *token) {
    // Detects invalid identifiers like `a5` which start with a letter and contain numbers or special characters in an invalid format
    if (isalpha(token[0])) {
        for (int i = 1; i < strlen(token); i++) {
            if (isdigit(token[i])) {
                return 1;
            }
        }
    }
    return 0;
}

int isPreprocessorDirective(char *token) {
    return token[0] == '#';
}


int isLiteral(char *token) {
    int len = strlen(token);
    return (token[0] == '"' && token[len - 1] == '"');
}

int main() {
    char tokens[100][20];
    int count = 0;

    printf("Enter the code (or use 'lexical < input.txt' to read from file):\n");

    // Read input from standard input
    while (scanf("%s", tokens[count]) != EOF && count < 100) {
        count++;
    }

    printf("\nLexical Analysis:\n");

    for (int i = 0; i < count; i++) {
        if (isPreprocessorDirective(tokens[i])) {
            printf("%s is a preprocessor directive\n", tokens[i]);
        } else if (isKeyword(tokens[i])) {
            printf("%s is a keyword\n", tokens[i]);
        } else if (isOperator(tokens[i])) {
            printf("%s is an operator\n", tokens[i]);
        } else if (isNumber(tokens[i])) {
            printf("%s is a number\n", tokens[i]);
        } else if (isLiteral(tokens[i])) {
            printf("%s is a literal\n", tokens[i]);
        } else if (isInvalidIdentifier(tokens[i])) {
            printf("%s is an invalid identifier\n", tokens[i]);
        } else if (isIdentifier(tokens[i])) {
            printf("%s is an identifier\n", tokens[i]);
        } else {
            printf("%s is a special character\n", tokens[i]);
        }
    }

    return 0;
}
