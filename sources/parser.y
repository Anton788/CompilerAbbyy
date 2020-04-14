%{

#include <kParser.hpp>
#include <kLexer.h>
#include <iostream>

using namespace std;

int kerror( yyscan_t scanner, Expression*& result, const char* msg )
{
    cerr << "kerror called: '" << msg << "'" << endl;
    return 0;
}

%}

%code requires
{

#include <SyntaxTree.h>


#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

#define YYSTYPE KSTYPE

}

%define api.prefix {k}
%define api.pure
%param { yyscan_t scanner }
%parse-param { Expression*& result }

%union {
    int Number;
    Expression* Exp;
}

%token MUL
%token PLUS
%token <Number> NUMBER
%type <Exp> Expression

%left PLUS
%left MUL

%destructor { delete $$; } Expression

%%

Start: Expression[E] { result = $E; }
;

Expression: NUMBER[N] { $$ = new NumExpression( $N ); }
    | Expression[L] PLUS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Plus, $R ); }
    | Expression[L] MUL Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Mul, $R ); }
;