#pragma once

#include <memory>
#include <Visitor.h>
#include <assert.h>
#include <vector>
#include <iostream>


class Statement {
public:
    virtual void accept(Visitor* ) const  = 0;
};

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
        OC_And,
        OC_Minus,
        OC_Less,
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

class BoolExpression : public Expression {
public:
    BoolExpression( bool _value ) : value( _value ) {}

    bool Value() const { return value; }

    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }
private:
    const bool value;
};

class ArgumentList{
public:
    ArgumentList(){}
    ArgumentList(Expression* e){
        argumentList.push_back(e);
    }

    ArgumentList(Expression* e, ArgumentList* list){
        list->argumentList.swap(argumentList);
        argumentList.insert(argumentList.begin(), e);
    }
    const std::vector<Expression*> & getArgList() const{
        return argumentList;
    }

private:
    std::vector<Expression*> argumentList;
};

class IdExpression : public  Expression{
public:
    IdExpression(std::string s){
        value = s;
    }
    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }

    std::string getId() const  {
        return value;
    }
private:
    std::string value;
};

class ExpressionLength : public Expression {
public:
    ExpressionLength(Expression* expr_):
    expr(expr_)
    {
        //this->length = expr.length();
    }
    virtual void accept(Visitor* v) const override{
        assert( v != 0 );
        v->visit( this );
    }
/*    int getLength(){
        return length;
    }*/
    const Expression* getExpr() const{
        return expr.get();
    }
private:
    std::unique_ptr<Expression> expr;
    int length;
};

class ExpressionNewInt: public Expression{
public:
    ExpressionNewInt(Expression* expr_):
    expr(expr_)
    {}
    virtual void accept(Visitor* v) const override{
        assert( v != 0 );
        v->visit( this );
    }
    const Expression* getExpr() const {
        return expr.get();
    }
private:
    std::unique_ptr<Expression> expr;
};

class ExpressionSquare: public Expression{
public:
    ExpressionSquare(Expression* parent_, Expression* expr_):
    parent_expr(parent_),
    expr(expr_)
    {}
    virtual void accept(Visitor* v) const override{
        assert( v != 0 );
        v->visit( this );
    }

    const Expression* getParent() const {
        return parent_expr.get();
    }

    const Expression* getIndex() const {
        return expr.get();
    }

private:
    std::unique_ptr<Expression> parent_expr;
    std::unique_ptr<Expression> expr;
};

class ExpressionNewId: public Expression{
public:
    ExpressionNewId(std::string expr_):
    expr(new IdExpression(expr_))
    {
    }
    virtual void accept(Visitor* v) const override{
        assert( v != 0 );
        v->visit( this );
    }
    const Expression* getExpr() const {
        return expr.get();
    }
private:
    std::unique_ptr<IdExpression> expr;
};

/*class ExpressionNegation: public Expression{
public:
    ExpressionNegation(Expression* expr){
        this->expr = expr;
    }
    virtual void accept(Visitor* v) const override{
        assert( v != 0 );
        v->visit( this );
    }
private:
    Expression* expr;
};*/


class CallExpression: public Expression{
public:
    CallExpression( char* str,ArgumentList* list) :argumentsPtr(list), identifier(str){}

    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }
    const ArgumentList* getArgs() const {
        return argumentsPtr.get();
    }
    std::string getId() const{
        return identifier;
    }
private:
    std::string identifier;
    std::unique_ptr<ArgumentList> argumentsPtr;
};

/*
class UnaryExpression : public Expression {
public:
    ThisExpression() : value( -1 ) {}

    int Value() const { return value; }

    virtual void accept( Visitor* v ) const override { assert( v != 0 ); v->visit( this ); }
private:
    const int value;
};

*/


