#include "SymbolVisitor.h"
#include <SyntaxTree.h>

void VisitorSymtableBuilder::visit(const NumExpression *expr) {}

void VisitorSymtableBuilder::visit(const BinopExpression *expr) {}

void VisitorSymtableBuilder::visit(const BoolExpression *expr) {}

void VisitorSymtableBuilder::visit(const IdExpression *expr) {}

void VisitorSymtableBuilder::visit(const ExpressionSquare *expr) {}

void VisitorSymtableBuilder::visit(const ExpressionLength *expr) {}

void VisitorSymtableBuilder::visit(const ExpressionNegation *expr) {}

void VisitorSymtableBuilder::visit(const ThisExpression *expr) {}

void VisitorSymtableBuilder::visit(const AssignArrayState *statement) {}

void VisitorSymtableBuilder::visit(const AssignState *statement) {}

void VisitorSymtableBuilder::visit(const IntType *type) {}

void VisitorSymtableBuilder::visit(const ObjState *objStatement) {}

void VisitorSymtableBuilder::visit(const VarDeclaration *var_declaration) {}

void VisitorSymtableBuilder::visit(const MethodBody *method_body) {}

void VisitorSymtableBuilder::visit(const MethodDeclaration *method_declaration) {
    PMethodInfo method_info = std::make_shared<MethodInfo>(method_declaration->getID()->getId(),
                                                           method_declaration->getType()->getType());
    for (const auto &param: method_declaration->getMethodList()->getArgList()) {
        method_info->addParam(param.second->getId(), param.first->getType());
    }
    for (const auto &var: method_declaration->getBody()->getVarList()->getVarList()) {
        method_info->addVar(var);
    }
    last_method_ = method_info;
}

void VisitorSymtableBuilder::visit(const MainClass *main_class) {}

void VisitorSymtableBuilder::visit(const Goal *goal) {
    for (const auto &pclass: goal->getClassList()->getArgList()) {
        pclass->accept(this);
    }
    table_->Print();
}

void VisitorSymtableBuilder::visit(const ExpressionNewId *expr) {}

void VisitorSymtableBuilder::visit(const ExpressionNewInt *expr) {}

void VisitorSymtableBuilder::visit(const BoolType *type) {};

void VisitorSymtableBuilder::visit(const ArrayIntType *type) {};

void VisitorSymtableBuilder::visit(const IdType *type) {};

void VisitorSymtableBuilder::visit(const ClassDeclaration *class_var) {
    // class_var->accept(this);
    PClassInfo current;
    if (class_var->getExtendsName() == nullptr) {
        current = std::make_shared<ClassInfo>(class_var->getClassName()->getId());
    } else {
        current = std::make_shared<ClassInfo>(class_var->getClassName()->getId(),
                                                         class_var->getExtendsName()->getId());
    }
    for (const auto &var: class_var->getVarList()->getVarList()) {
        current->addVar(var);
    }
    for (const auto &method: class_var->getMethodList()->getList()) {
        method->accept(this);
        current->addMethod(last_method_);
    }
    table_->addClass(current);
};

void VisitorSymtableBuilder::visit(const CallExpression *expr) {};

void VisitorSymtableBuilder::visit(const PrintState *statement) {};

void VisitorSymtableBuilder::visit(const WhileState *statement) {};

void VisitorSymtableBuilder::visit(const ConditionState *statement) {};

void VisitorSymtableBuilder::visit(const StatementList *statement) {};


