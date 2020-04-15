%{
#include <kParser.hpp>
#include <string>
#include <iostream>

using namespace std;
int yylen;
%}

%option prefix="k"
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge


L_IS_EQUAL "=="
L_AND "&&"
L_LESS "<"
L_MUL "*"
L_MINUS "-"
L_PLUS "+"
L_ASSIGN     "="
L_SPACE      [\n\r\t ]+
L_DOT_COMMA ";"
L_DOT "."
L_COMMA ","
L_UNARY_NEGATION "!"

L_IF         "if"
L_ELSE       "else"
L_WHILE      "while"
L_CLASS      "class"
L_STATIC     "static"
L_VOID       "void"
L_MAIN       "main"
L_EXTENDS    "extends"
L_RETURN     "return"
L_PUBLIC     "public"
L_PRINT       "System.out.println"
L_LENGTH     "length"
L_NEW        "new"
L_THIS       "this"
L_TRUE       "true"
L_FALSE      "false"
L_STRING     "String"
L_BOOLEAN    "boolean"
L_INT        "int"
L_DIGIT      [0-9]
L_LETTER     [a-zA-Z_]
L_INTEGER   [1-9]{L_DIGIT}*|0
L_LOGIC     {L_TRUE}|{L_FALSE}
L_ID         {L_LETTER}({L_DIGIT}|{L_LETTER})*
L_COMMENT    (\/\/.*)|(\/\*((.|\n)*?)\*\/)
L_LBRACKET "("
L_RBRACKET ")"
L_LSQUAREBRACKET "["
L_RSQUAREBRACKET "]"
L_LBRACE "{"
L_RBRACE "}"

%%


{L_IS_EQUAL}  { cout << "IS_EQUAL "; return IS_EQUAL; }
{L_AND}  {
             cout << "AND "; return AND;
         }
{L_LESS} {
             cout << "LESS "; return LESS;
         }
{L_MINUS}  {
               cout << "MINUS "; return MINUS;
           }

{L_MUL} {
    cout << "MUL "; return MUL;
}
{L_PLUS} {
    cout << "PLUS "; return PLUS;
}


{L_LBRACKET} {
    cout << "LBRACKET "; return LBRACKET;
}

{L_RBRACKET} {
    cout << "RBRACKET "; return RBRACKET;
}

{L_LSQUAREBRACKET} {
    cout << "LSQUAREBRACKET "; return LSQUAREBRACKET;
}

{L_RSQUAREBRACKET} {
    cout << "RSQUAREBRACKET "; return RSQUAREBRACKET;
}

{L_LBRACE} {
    cout << "LBRACE "; return LBRACE;
}

{L_RBRACE} {
    cout << "RBRACE "; return RBRACE;
}

{L_DOT} {
    cout << "DOT "; return DOT;
}


{L_UNARY_NEGATION} {
    cout << "UNARY_NEGATION "; return UNARY_NEGATION;
}



{L_EXTENDS} {
    cout << "EXTENDS ";
    return EXTENDS;

}


{L_BOOLEAN} {
    cout << "BOOLEAN "; return BOOLEAN;
}


{L_ELSE} {
    cout<<"ELSE "; return ELSE;
}

{L_PRINT} {
    cout << "PRINT "; return PRINT;
}

{L_WHILE} {
    cout<<"WHILE "; return WHILE;
}

{L_IF} {
    cout<<"IF "; return IF;
}

{L_COMMA} {
    cout<<"COMMA "; return COMMA;
}

{L_STATIC} {
    cout<<"STATIC "; return STATIC;
}

{L_CLASS} {
    cout<<"CLASS "; return CLASS;
}

{L_MAIN} {
    cout<<"MAIN "; return MAIN;
}

{L_STRING} {
    cout<<"STRING "; return STRING;
}

{L_VOID} {
    cout<<"VOID "; return VOID;
}

{L_PUBLIC} {
    cout<<"PUBLIC "; return PUBLIC;
}

{L_RETURN} {
    cout<<"RETURN "; return RETURN;
}

{L_INT} {
    cout << "INT "; return INT;
}


{L_DOT_COMMA} {
    cout << "DOT_COMMA "; return DOT_COMMA;
}


{L_ASSIGN} {
    cout << "ASSIGN "; return ASSIGN;
}


{L_INTEGER} {
    yylval->Number = (atoi(yytext));
    cout << "INTEGER ";
    return INTEGER;
}

{L_LOGIC} {
    //запомнить
    cout << "LOGICAL ";
    return LOGICAL;
}

{L_LENGTH} {
    cout << "LENGTH "; return LENGTH;
}

{L_NEW} {
    cout << "NEW "; return NEW;
}

{L_THIS} {
    cout << "THIS ";
    return THIS;
}

{L_ID} {
    //запомнить
    cout << "ID ";
    return ID;
}

{L_COMMENT} {
}

{L_SPACE} {
}



.               printf("ERROR ");
%%