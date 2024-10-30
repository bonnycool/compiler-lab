%{
#include <stdio.h>

int i;
%}

%%

[a-zA-Z]+  { 
    for (i = 0; i < yyleng; i++) {
        if (yytext[i] == 'a' && yytext[i+1] == 'b' && yytext[i+2] == 'c') {
            yytext[i] = 'A';
            yytext[i+1] = 'B';
            yytext[i+2] = 'C';
        }
    }
    printf("%s", yytext);  // Print the modified string
}

[ \t\n]+  {
    printf("%s", yytext);  // Print spaces, tabs, or newlines as-is
}

. ;

%%

int main() {
    printf("Enter string:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
