#pragma once

#include <memory>
#include <Visitor.h>
#include <assert.h>

class Expression {
public:
    virtual void accept( Visitor* ) const = 0;
};

class NumExpression : public Expression {
public:
    NumExpression( int _value ) : value( _value ) {}

    int Value() const { return value; }

    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }

private:
    const int value;
};

class BinopExpression : public Expression {
public:
    enum TOpCode {
        OC_Plus,
        OC_Mul,
    };
    BinopExpression( Expression* _left, TOpCode _code, Expression* _right ) :
            code( _code ),
            left( _left ),
            right( _right )
    {
        assert( left != 0 );
        assert( right != 0 );
    }

    const Expression* Left() const { return left.get(); }
    const Expression* Right() const { return right.get(); }
    TOpCode OpCode() const { return code; }

    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }

private:
    const TOpCode code;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};