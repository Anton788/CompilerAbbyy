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

%token IS_EQUAL
%token AND
%token LESS
%token MINUS
%token MUL
%token PLUS
%token FALSE
%token TRUE



%token<Number> INTEGER
%token<std::string> ID
%token PUBLIC
%token EXTENDS
%token RETURN
%token INT
%token BOOLEAN
%token ASSIGN
%token DOT_COMMA
%token LBRACKET
%token RBRACKET
%token LSQUAREBRACKET
%token RSQUAREBRACKET
%token LBRACE
%token RBRACE
%token DOT
%token COMMA
%token LENGTH
%token UNARY_NEGATION
%token THIS
%token MAIN
%token CLASS
%token VOID
%token IF
%token ELSE
%token WHILE
%token PRINT
%token STRING
%token STATIC
%token END 0 "end of file"
%token NEW

%left IS_EQUAL
%left AND
%left PLUS MINUS
%left MUL

%right UNARY_NEGATION

%right LBRACKET
%right LBRACE
%right LSQUAREBRACKET
%left IF
%left ELSE
%left COMMA
%left DOT
%left EXTENDS
%left RBRACKET
%left RBRACE
%left RSQUAREBRACKET

%type <Exp> Expression

%destructor { delete $$; } Expression

%%

Start: Expression[E] { result = $E; }
;

Expression: INTEGER[N] { $$ = new NumExpression( $N ); }
    | TRUE { $$ = new BoolExpression( true ); }
    | FALSE { $$ = new BoolExpression( false ); }
    | THIS {$$ = new ThisExpression(); }
    | LBRACKET Expression[N] RBRACKET { $$ = $N;}
    | Expression[L] PLUS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Plus, $R ); }
    | Expression[L] MUL Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Mul, $R ); }
    | Expression[L] MINUS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Minus, $R ); }
    | Expression[L] LESS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Less, $R ); }
    | Expression[L] AND Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_And, $R ); }
;
