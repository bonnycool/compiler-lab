%{
#include <stdio.h>
%}

letter  [a-zA-Z]
digit   [0-9]
keyword "auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"main"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"printf"

operator "&&"|"||"|"=="|"<="|">="|"!="|"+"|"-"|"*"|"/"|"%"|"&"|"|"|"!"|"="
special_char "{"|"}"|"["|"]"|"("|")"|"#"|":"|";"|","|"."|"'"|"\""|"\\"

quotes "'"|"\""
%%

#include.*                               printf("\n%s is a preprocessor directive", yytext); 
#[^"'\n]                             printf("\n is an invalid preprocessor directive",yytext);

{quotes}([^"\n&\\]|{special_char})*{quotes}    printf("\n%s is a literal",yytext);

{digit}+("."{digit}*)?([eE]("+"|"-")?{digit}+)?  printf("\n%s is a real number", yytext);
{digit}+"."{digit}*([eE]("+"|"-")?{digit}+)?    printf("\n%s is a floating point number", yytext);
{keyword}                           printf("\n%s is a keyword", yytext);

{letter}+{digit}+  printf("\n %s invalid",yytext);
{letter}({letter}|{digit})*         printf("\n%s is an identifier", yytext);
{operator}                          printf("\n%s is an operator", yytext);
{special_char}                      printf("\n%s is a special character", yytext);


\n
%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}
