#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <memory>

#include <SyntaxTree.h>

#include <SymbolTable.hpp>
#include <Visitor.h>

class VisitorSymtableBuilder : public Visitor {
public:
    VisitorSymtableBuilder() : table_(std::make_shared<TableGlobal>()) {}

    std::shared_ptr<TableGlobal> getTable() {
        return table_;
    };

    virtual void visit(const NumExpression *expr);

    virtual void visit(const BinopExpression *expr);

    virtual void visit(const BoolExpression *expr);

    virtual void visit(const IdExpression *expr);

    virtual  void visit(const ExpressionSquare *expr);

    virtual void visit(const ExpressionLength *expr);

    virtual void visit(const ExpressionNegation *expr);

    virtual void visit(const ThisExpression *expr);

    virtual void visit(const AssignState *statement);

    virtual  void visit(const IntType *type);

    virtual void visit(const BoolType *type);

    virtual void visit(const ArrayIntType *type);

    virtual void visit(const IdType *type);

    virtual void visit(const VarDeclaration *var_declaration);

    virtual void visit(const MethodBody *method_body);

    virtual void visit(const MethodDeclaration *method_declaration);

    virtual void visit(const ClassDeclaration *class_var);

    virtual void visit(const MainClass *main_class);

    virtual void visit(const Goal *goal);

    virtual void visit(const ExpressionNewId *expr);

    virtual void visit(const ExpressionNewInt *expr);

    virtual void visit(const CallExpression *expr);

    virtual void visit(const AssignArrayState *statement);

    virtual void visit(const PrintState *statement);

    virtual void visit(const WhileState *statement);

    virtual void visit(const ConditionState *statement);
    virtual void visit (const ObjState* objStatement);
    virtual void visit(const StatementList *statement);

private:
    PTableGlobal table_;
    PMethodInfo last_method_;
};
