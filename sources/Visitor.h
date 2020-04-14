#pragma once

class BinopExpression;
class NumExpression;

class Visitor {
public:
    virtual void visit( const BinopExpression* ) = 0;
    virtual void visit( const NumExpression* ) = 0;
};

class CompVisitor : public Visitor {
public:
    virtual void visit( const BinopExpression* );
    virtual void visit( const NumExpression* );

    int GetValue() const { return subtreeValue; }

private:
    int subtreeValue = 0;
};