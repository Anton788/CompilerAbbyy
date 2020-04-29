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
class ObjState;
class PrintState;
class ConditionState;
class ArrayIntType;
class BoolType;
class IntType;
class IdType;
class VarDeclaration;
class MethodBody;
class MethodDeclaration;

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
    virtual void visit (const ObjState*) = 0;
    // virtual void visit( const SquareBracketExpression* ) = 0;
    virtual void visit (const PrintState*) = 0;
    virtual void visit (const ConditionState*) = 0;
    virtual void visit (const ArrayIntType*) = 0;
    virtual void visit (const BoolType*) = 0;
    virtual void visit (const IntType*) = 0;
    virtual void visit (const IdType*) = 0;
    virtual void visit (const VarDeclaration*) = 0;
    virtual void visit (const MethodBody*) = 0;
    virtual void visit (const MethodDeclaration*) = 0;
};
