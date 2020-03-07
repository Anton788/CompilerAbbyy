%option reentrant noyywrap never-interactive nounistd


%{

#include <string>
#include <iostream>
#include "Commands.h"

int yylen;
%}
DIGIT [0-9]
LETTER [a-zA-Z]
Id {LETTER}({DIGIT}|{LETTER})*
IntegerLiteral [1-9]{DIGIT}*|0


%%

"class" std::cout<<"CLASS";
"extend" std::cout<<"EXTENDS";
{Id} std::cout<<"ID ("<<std::string(yytext,yylen)<<")";

%%
