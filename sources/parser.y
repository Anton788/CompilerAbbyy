%{

#include <kParser.hpp>
#include <kLexer.h>
#include <iostream>

using namespace std;

int kerror( yyscan_t scanner, Statement*& result, const char* msg )
{
    cerr << "kerror called: '" << msg << "'" << endl;
    return 0;
}

%}

%code requires{
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
%parse-param { Statement*& result }

%union {
    int Number;
    char* Identifier;
    Expression* Exp;
    ArgumentList* ExpressionList;
    Statement* State;
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
%token<Identifier> ID
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

%left ASSIGN
%left AND
%left LESS
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
%type <ExpressionList> ExpressionList
%type <State> Statement


%destructor { delete $$; } Expression

%%

Start: Statement[E] { result = $E; }
;

Statement:
	LBRACE StatementList[S] RBRACE {$$=new ObjState($S);}
	| IF LBRACKET Expression[I] RBRACKET Statement ELSE Statement[E] {$$=new ConditionState($I, $E); }
	| WHILE LBRACKET Expression[E] RBRACKET Statement[S] {$$ = new WhileState($E, $S);}
	|ID[I] ASSIGN Expression[E] DOT_COMMA {$$ = new AssignState($I, $E);}
	| PRINT LBRACKET Expression[N] RBRACKET DOT_COMMA {$$ =new PrintState($N);}
	|ID[I] LSQUAREBRACKET Expression[E] RSQUAREBRACKET ASSIGN Expression[L] DOT_COMMA {
	$$ = new AssignArrayState($I, $E, $L); }


StatementList: %empty {$$ = new StatementList(); }
| Statement[L] StatementList[R] { $$ = new StatementList($L, $R);}



Expression: Expression[L] MUL Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Mul, $R ); }
    | Expression[L] PLUS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Plus, $R ); }
    | Expression[L] MINUS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Minus, $R ); }
    | Expression[L] AND Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_And, $R ); }
    | Expression[L] LESS Expression[R] { $$ = new BinopExpression( $L, BinopExpression::OC_Less, $R ); }
    | Expression[F] LSQUAREBRACKET Expression[E] RSQUAREBRACKET {$$ = new ExpressionSquare($F, $E);}
    | Expression[L] DOT LENGTH {$$ = new ExpressionLength( $L);}
    | Expression[L] DOT ID[I] LBRACKET ExpressionList[E] RBRACKET {
            $$ = new CallExpression($I, $E, $L);}
    | INTEGER[N] { $$ = new NumExpression( $N ); }
    | TRUE { $$ = new BoolExpression( true ); }
    | FALSE { $$ = new BoolExpression( false ); }
    | ID[N] {$$ = new IdExpression($N);}
    | THIS {$$ = new ThisExpression(); }
    | NEW INT LSQUAREBRACKET Expression[E] RSQUAREBRACKET {$$ = new ExpressionNewInt($E);}
    | NEW ID[I] LBRACKET RBRACKET {$$ = new ExpressionNewId($I);}
    | LBRACKET Expression[N] RBRACKET { $$ = $N;}
    | UNARY_NEGATION Expression[E] {$$ = new ExpressionNegation($E);}
;

/*Expressions:
    %empty {
        $$ = Expressions();
    }
    | Expression {
        $$ = Expressions();
        $$.push_back(std::move($1));
    }
    | Expressions "," Expression {
        $1.push_back(std::move($3));
        $$ = std::move($1);
    }
;*/

ExpressionList: Expression[L] COMMA ExpressionList[R]{$$ = new ArgumentList($L, $R);}
| Expression[N] {$$ = new ArgumentList($N);}
| %empty {$$ = new ArgumentList();}
