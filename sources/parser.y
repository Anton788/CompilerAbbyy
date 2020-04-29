%{

#include <kParser.hpp>
#include <kLexer.h>
#include <iostream>

using namespace std;

int kerror( yyscan_t scanner, Goal*& result, const char* msg )
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
%parse-param {Goal*& result }

%union {
    int Number;
    char* Identifier;
    Expression* Exp;
    ArgumentList* ExpressionList;
    Statement* State;
    StatementList* StateList;
    Type* Typ;
    VDeclaration* VarD;
    VarDeclarationList* VarDList;
    MethodList* MArg;
    MethodBody* MBode;
    MethodDeclaration* MDec;
    MethodDeclarationClass* MDClass;
    ClassDeclaration* ClassD;
    MainClass* MainCl;
    ClassDeclarations* ClassList;
    Goal* Gl;
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
%type <StateList> StatementList
%type <Typ> Type
%type <VarD> VDeclaration
%type <VarDList> Var_declarationList
%type <MArg> MethodList
%type <MBode> MethodBody
%type <MDec> MethodDeclaration
%type <MDClass> MethodDeclarationClass
%type <ClassD> ClassDeclaration
%type <MainCl> MainClass
%type <ClassList> ClassDeclarations
%type <Gl> Goal


%destructor { delete $$; } Expression
%destructor { delete $$; } Statement
%%

Start: Goal[E] { result = $E; }


Goal: MainClass[M] ClassDeclarations[C] END {$$ = new Goal($M, $C);}

ClassDeclarations: %empty {$$ = new ClassDeclarations();}
    | ClassDeclarations[L] ClassDeclaration[C] { $$ = new ClassDeclarations($C, $L); }


MainClass : CLASS ID[I] LBRACE PUBLIC STATIC VOID MAIN LBRACKET STRING LSQUAREBRACKET RSQUAREBRACKET ID[N] RBRACKET LBRACE Statement[S] RBRACE RBRACE{ $$ = new MainClass($I, $N, $S);}

ClassDeclaration: CLASS ID[I] LBRACE Var_declarationList[V] MethodDeclarationClass[M] RBRACE {$$ = new ClassDeclaration($V, $M, $I);}
	|CLASS ID[I] EXTENDS ID[N] LBRACE Var_declarationList[V] MethodDeclarationClass[M] RBRACE {$$ = new ClassDeclaration($V, $M, $I, $N);}

MethodDeclarationClass:MethodDeclarationClass[L] MethodDeclaration[V]  { $$ = new MethodDeclarationClass($V, $L); }
                            |%empty {$$ = new MethodDeclarationClass(); }

MethodList: Type[T] ID[I] COMMA MethodList[A] {$$ = new MethodList($T, $I, $A);}
          | Type[T] ID[I] {$$ = new MethodList($T, $I);}
           | %empty {$$ = new MethodList();}

MethodBody: LBRACE Var_declarationList[V] StatementList[S] RETURN Expression[E] DOT_COMMA RBRACE {$$ = new MethodBody($V, $S, $E);}

MethodDeclaration: PUBLIC Type[T] ID[I] LBRACKET MethodList[A] RBRACKET MethodBody[B] {$$ = new MethodDeclaration($T, $I, $A, $B);};

VDeclaration : Type[T] ID[I] DOT_COMMA {$$ = new VarDeclaration($T, $I);}

Var_declarationList  : Var_declarationList[L] VDeclaration[V]  { $$ = new VarDeclarationList($V, $L); }
    |%empty {$$ = new VarDeclarationList(); }

Type: INT LSQUAREBRACKET RSQUAREBRACKET {$$=new ArrayIntType();}
     | BOOLEAN {$$=new BoolType();}
     | INT {$$=new IntType();}
     | ID[I]  {$$ = new IdType($I);}

Statement: LBRACE StatementList[S] RBRACE {$$=new ObjState($S);}
	| ID[I] LSQUAREBRACKET Expression[E] RSQUAREBRACKET ASSIGN Expression[L] DOT_COMMA { $$ = new AssignArrayState($I, $E, $L); }
	| WHILE LBRACKET Expression[E] RBRACKET Statement[S] {$$ = new WhileState($E, $S);}
	| ID[I] ASSIGN Expression[E] DOT_COMMA {$$ = new AssignState($I, $E);}
	| PRINT LBRACKET Expression[N] RBRACKET DOT_COMMA {$$ =new PrintState($N);}
	| IF LBRACKET Expression[I] RBRACKET Statement[N] ELSE Statement[E] {$$=new ConditionState($I, $N, $E); }

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
