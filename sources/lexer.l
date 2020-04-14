%{
#include <kParser.hpp>
#include <string>
#include <iostream>


int yylen;
%}

%option prefix="k"
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge





DIGIT           [0-9]
LETTER          [a-zA-Z]
Id              {LETTER}({DIGIT}|{LETTER})*
Integer         [1-9]{DIGIT}*|0
Operation       ( "&&" | "<" | "+" | "-" | "*" )
SPACE           [\n\r\t ]+

%%

{Id}            printf("ID ");
{Integer}       printf("INT ");
{SPACE}     printf("");
"class"         printf("CLASS ");
"public"        printf("PUBLIC ");
"static"        printf("STATIC ");
"void"          printf("VOID ");
"main"          printf("MAIN ");
"extends"       printf("EXTENDS ");
"return"        printf("RETURN ");

"String"        printf("STRING ");
"int"           printf("INT ");
"boolean"       printf("BOOL ");

";"             printf("SEMI ");
"="             printf("ATTR ");
"."             printf("DOT ");
"!"             printf("NOT ");

"&&"            printf("AND ");
"<"             printf("LESS ");
"+"             printf("ADD ");
"-"             printf("SUB ");
"*"             printf("MUL ");

"("             printf("L_BRACE ");
")"             printf("R_BRACE ");
"["             printf("LSQ_BRACE ");
"]"             printf("RSQ_BRACE ");
"{"             printf("LF_BRACE ");
"}"             printf("RF_BRACE ");

"if"            printf("IF ");
"else"          printf("ELSE ");
"while"         printf("WHILE ");
"System.out.println"    printf("OUT ");

"length"        printf("LEN ");
"this"          printf("THIS ");
"new"           printf("NEW ");

"true"          printf("TRUE ");
"false"         printf("FALSE ");



.               printf("ERROR ");
%%