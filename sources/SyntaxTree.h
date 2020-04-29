#pragma once

#include <memory>
#include <Visitor.h>
#include <assert.h>
#include <vector>
#include <iostream>


using namespace std;

class Expression {
public:
    virtual void accept(Visitor *) const = 0;
};


class Statement {
public:
    virtual void accept(Visitor *) const = 0;
};

class Type {
public:
    virtual void accept(Visitor *) const = 0;
};

class VDeclaration {
public:
    virtual void accept(Visitor *) const = 0;
};
class MDeclaration{
public:
    virtual void accept(Visitor *) const = 0;
};
class NumExpression : public Expression {
public:
    NumExpression(int _value) : value(_value) {}

    int Value() const { return value; }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

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

    BinopExpression(Expression *_left, TOpCode _code, Expression *_right) :
            code(_code),
            left(_left),
            right(_right) {
        assert(left != 0);
        assert(right != 0);
    }

    const Expression *Left() const { return left.get(); }

    const Expression *Right() const { return right.get(); }

    TOpCode OpCode() const { return code; }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    const TOpCode code;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class BoolExpression : public Expression {
public:
    BoolExpression(bool _value) : value(_value) {}

    bool Value() const { return value; }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    const bool value;
};

class ArgumentList {
public:
    ArgumentList() {}

    ArgumentList(Expression *e) {
        argumentList.push_back(e);
    }

    ArgumentList(Expression *e, ArgumentList *list) {
        list->argumentList.swap(argumentList);
        argumentList.insert(argumentList.begin(), e);
    }

    const std::vector<Expression *> &getArgList() const {
        return argumentList;
    }

private:
    std::vector<Expression *> argumentList;
};

class IdExpression : public Expression {
public:
    IdExpression(std::string s) {
        value = s;
        cout << s;
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    std::string getId() const {
        return value;
    }

private:
    std::string value;
};

class ExpressionLength : public Expression {
public:
    ExpressionLength(Expression *expr_) :
            expr(expr_) {
        //this->length = expr.length();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

/*    int getLength(){
        return length;
    }*/
    const Expression *getExpr() const {
        return expr.get();
    }

private:
    std::unique_ptr<Expression> expr;
    int length;
};

class ExpressionNewInt : public Expression {
public:
    ExpressionNewInt(Expression *expr_) :
            expr(expr_) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Expression *getExpr() const {
        return expr.get();
    }

private:
    std::unique_ptr<Expression> expr;
};

class ExpressionSquare : public Expression {
public:
    ExpressionSquare(Expression *parent_, Expression *expr_) :
            parent_expr(parent_),
            expr(expr_) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Expression *getParent() const {
        return parent_expr.get();
    }

    const Expression *getIndex() const {
        return expr.get();
    }

private:
    std::unique_ptr<Expression> parent_expr;
    std::unique_ptr<Expression> expr;
};

class ThisExpression : public Expression {
public:
    ThisExpression() = default;

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }
};

class ExpressionNewId : public Expression {
public:
    ExpressionNewId(std::string expr_) :
            expr(new IdExpression(expr_)) {
        cout << expr_;
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Expression *getExpr() const {
        return expr.get();
    }

private:
    std::unique_ptr<IdExpression> expr;
};

class ExpressionNegation : public Expression {
public:
    ExpressionNegation(Expression *expr_) :
            expr(expr_) {
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Expression *getExpr() const {
        return expr.get();
    }

private:
    std::unique_ptr<Expression> expr;
};


class CallExpression : public Expression {
public:
    CallExpression(char *str, ArgumentList *list, Expression *parent_) : argumentsPtr(list), identifier(str),
                                                                         parent(parent_) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const ArgumentList *getArgs() const {
        return argumentsPtr.get();
    }

    std::string getId() const {
        return identifier;
    }

    const Expression *getExpr() const {
        return parent.get();
    }

private:
    std::string identifier;
    std::unique_ptr<ArgumentList> argumentsPtr;
    std::unique_ptr<Expression> parent;
};

class AssignArrayState : public Statement {
public:
    AssignArrayState(std::string name_array, Expression *index, Expression *value) :
            name_array(name_array),
            index(index),
            value(value) {}

    std::string getArray() const { return name_array; }

    const Expression *getIndex() const {
        return index.get();
    }

    const Expression *getValue() const {
        return value.get();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    std::string name_array;
    std::unique_ptr<Expression> index;
    std::unique_ptr<Expression> value;
};

class AssignState : public Statement {
public:
    AssignState(std::string state, Expression *value) :
            state(state),
            value(value) {}

    std::string getState() const { return state; }

    const Expression *getValue() const {
        return value.get();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    std::string state;
    std::unique_ptr<Expression> value;
};

class WhileState : public Statement {
public:
    WhileState(Expression *value, Statement *state) :
            state(state),
            value(value) {}

    const Statement *getState() const {
        return state.get();
    }

    const Expression *getValue() const {
        return value.get();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    std::unique_ptr<Statement> state;
    std::unique_ptr<Expression> value;
};


class StatementList {
public:
    StatementList() {}

    StatementList(Statement *e, StatementList *list) {
        list->statementList.swap(statementList);
        statementList.insert(statementList.begin(), e);
    }

    const std::vector<Statement *> &getStList() const {
        return statementList;
    }

private:
    std::vector<Statement *> statementList;
};

class ObjState : public Statement {
public:
    ObjState(StatementList *list) : statementsPtr(list) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const StatementList *getList() const {
        return statementsPtr.get();
    }

private:
    std::unique_ptr<StatementList> statementsPtr;
};

class PrintState : public Statement {
public:
    PrintState(Expression *value) :
            value(value) {}

    const Expression *getValue() const {
        return value.get();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    std::unique_ptr<Expression> value;
};

class ConditionState : public Statement {
public:
    ConditionState(Expression *value, Statement *StateIF, Statement *StateElse) :
            state_if(StateIF),
            state_else(StateElse),
            value(value) {}

    const Statement *getStateIf() const {
        return state_if.get();
    }

    const Statement *getStateElse() const {
        return state_else.get();
    }

    const Expression *getValue() const {
        return value.get();
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

private:
    std::unique_ptr<Statement> state_if;
    std::unique_ptr<Statement> state_else;
    std::unique_ptr<Expression> value;
};

class ArrayIntType : public Type {
public:
    ArrayIntType() = default;

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }
};

class BoolType : public Type {
public:
    BoolType() = default;

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }
};

class IntType : public Type {
public:
    IntType() = default;

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }
};

class IdType : public Type {
public:
    IdType(IdExpression *exp) : value(exp) {
    }

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Expression *getValue() const {
        return value.get();
    }

private:
    std::unique_ptr<Expression> value;
};


class VarDeclarationList {
public:
    VarDeclarationList() {}

    VarDeclarationList(VDeclaration *e, VarDeclarationList *list) {
        list->argumentList.swap(argumentList);
        argumentList.insert(argumentList.begin(), e);
    }

    const std::vector<VDeclaration *> &getVarList() const {
        return argumentList;
    }

private:
    std::vector<VDeclaration *> argumentList;
};


class VarDeclaration : public VDeclaration {
public:
    VarDeclaration(Type * type, char *str) :
    typePtr(type), identifier(str) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Type *getType() const {
        return typePtr.get();
    }

    std::string getId() const {
        return identifier;
    }
private:
    std::unique_ptr<Type> typePtr;
    std::string identifier;
};


class MethodList {
public:
    MethodList() {}

    MethodList(Type *e, char* str) {
        argumentList.push_back(std::make_pair(e, str));
    }

    MethodList(Type *t, char* str, MethodList *list) {
        list->argumentList.swap(argumentList);
        argumentList.insert(argumentList.begin(), std::make_pair(t, str));
    }

    const std::vector<std::pair<Type*, char*> > &getArgList() const {
        return argumentList;
    }

private:
    std::vector<std::pair<Type*, char*> > argumentList;
};

class MethodBody: MDeclaration{
        public:
        MethodBody(VarDeclarationList * vList, StatementList* sList, Expression* e) :
        varDList(vList), statementList(sList), exp(e) {}

        virtual void accept(Visitor *v) const override {
                assert(v != 0);
                v->visit(this);
        }

        const VarDeclarationList *getVarList() const {
            return varDList.get();
        }

        const StatementList* getStatementList() const {
            return statementList.get();
        }

        const Expression* getExpression() const {
            return exp.get();
        }
        private:
        std::unique_ptr<VarDeclarationList> varDList;
    std::unique_ptr<StatementList> statementList;
    std::unique_ptr<Expression> exp;
};

class MethodDeclaration: MDeclaration{
public:
    MethodDeclaration(Type * t, char* str, MethodList* list_, MethodBody* body_) :
            typePtr(t), id(str), list(list_), body(body_) {}

    virtual void accept(Visitor *v) const override {
        assert(v != 0);
        v->visit(this);
    }

    const Type *getType() const {
        return typePtr.get();
    }

    const MethodList* getMethodList() const {
        return list.get();
    }

    const MethodBody* getBody() const {
        return body.get();
    }

    const std::string getID() const {
        return id;
    }
private:
    std::string id;
    std::unique_ptr<Type> typePtr;
    std::unique_ptr<MethodList> list;
    std::unique_ptr<MethodBody> body ;
};
