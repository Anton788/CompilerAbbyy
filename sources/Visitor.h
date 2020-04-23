#pragma once

class BinopExpression;
class NumExpression;
class BoolExpression;
class IdExpression;
class CallExpression;

class Visitor {
public:
    virtual void visit( const BinopExpression* ) = 0;
    virtual void visit( const NumExpression* ) = 0;
    virtual void visit( const BoolExpression* ) = 0;
    virtual void visit( const IdExpression* ) = 0;
    virtual void visit( const CallExpression* ) = 0;
   // virtual void visit( const SquareBracketExpression* ) = 0;


};
