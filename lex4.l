%{
#include <stdio.h>
int v = 0, c = 0;
%}

%%

[ \t\n]   ;
[aieouAEIOU]   { v++; }
[a-zA-Z]   { c++; }
.   ;

%%

int main() {
    printf("Enter string: ");
    yylex();
    printf("Vowels: %d\n", v);
    printf("Consonants: %d\n", c);
    return 0;
}

int yywrap() {
    return 1;
}
