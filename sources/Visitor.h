#pragma once

class BinopExpression;
class NumExpression;
class BoolExpression;
class ThisExpression;

class Visitor {
public:
    virtual void visit( const BinopExpression* ) = 0;
    virtual void visit( const NumExpression* ) = 0;
    virtual void visit( const BoolExpression* ) = 0;
    virtual void visit( const ThisExpression* ) = 0;


};

class CompVisitor : public Visitor {
public:
    virtual void visit( const BinopExpression* );
    virtual void visit( const NumExpression* );
    virtual void visit( const BoolExpression* ) ;
    virtual void visit( const ThisExpression* ) ;

    int GetValue() const { return subtreeValue; }

private:
    int subtreeValue = 0;
};
