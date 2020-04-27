#pragma once

class BinopExpression;
class NumExpression;
class BoolExpression;
class IdExpression;
class CallExpression;
class ExpressionLength;
class ExpressionSquare;
class ExpressionNewInt;
class ExpressionNewId;
class ThisExpression;
class ExpressionNegation;
class AssignArrayState;
class AssignState;
class WhileState;

class Visitor {
public:
    virtual void visit( const BinopExpression* ) = 0;
    virtual void visit( const NumExpression* ) = 0;
    virtual void visit( const BoolExpression* ) = 0;
    virtual void visit( const IdExpression* ) = 0;
    virtual void visit( const CallExpression* ) = 0;
    virtual void visit (const ExpressionLength* ) = 0;
    virtual void visit (const ExpressionSquare*) = 0;
    virtual void visit (const ExpressionNewInt*) = 0;
    virtual void visit (const ExpressionNewId*) = 0;
    virtual void visit (const ThisExpression*) = 0;
    virtual void visit (const ExpressionNegation*) = 0;
    virtual void visit (const AssignArrayState*) = 0;
    virtual void visit (const AssignState*) = 0;
    virtual void visit (const WhileState*) = 0;
    // virtual void visit( const SquareBracketExpression* ) = 0;

};
