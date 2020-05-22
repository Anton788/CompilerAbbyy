#include "TypeChecker.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>


void VisitorTypecheckerBuilder::visit(const Goal* goal) {
    // table_->Print();
    if (!checkCycle()) {
        return;
    }
    initTypes();
    AddParentClasses();
    //table_->Print();
    goal->getMainClass()->accept(this);
    std::unordered_set<std::string> class_names;
    for (const auto& pclass: goal->getClassList()->getArgList()) {
        if (class_names.find(pclass->getClassName()->getId()) == class_names.end()) {
            pclass->accept(this);
            class_names.insert(pclass->getClassName()->getId());
        }
        else {
            std::cout << "DefineError: Redefinition of class " << pclass->getClassName()->getId();
            //print_error_place(pclass->getPos());
        }
    }
}

void VisitorTypecheckerBuilder::visit(const MainClass* main_class) {
    curr_method_info_ = std::make_shared<MethodInfo>();
    main_class->getStatement()->accept(this);
}

void VisitorTypecheckerBuilder::visit(const ClassDeclaration* class_var) {

    curr_class_info_ = table_->getClass(class_var->getClassName()->getId());

    if ((class_var->getExtendsName() != nullptr) && (class_var->getExtendsName()->getId() != "" && !checkType(class_var->getExtendsName()->getId()))) {
        std::cout << "DefineERROR: Uknown parent class " << class_var->getExtendsName()->getId()<<endl;
    }


    std::unordered_set<std::string> vars;
    for (const auto& var: class_var->getVarList()->getVarList()) {
        if (vars.find(var->getId()->getId()) != vars.end()) {
            std::cout << "DefineError: Repeted definition of variable " << var->getId()->getId()<<endl;
        }
        vars.insert(var->getId()->getId());
        var->accept(this);
    }
    std::unordered_set<std::string> methods;
    for (const auto& method: class_var->getMethodList()->getList()) {
        if (methods.find(method->getID()->getId()) != methods.end()) {
            std::cout << "DefFuncError: repeted definition of function " << method->getID()->getId()<<endl;
            //print_error_place(method->getPos());
        }
        methods.insert(method->getID()->getId());
        method->accept(this);
    }

}

void VisitorTypecheckerBuilder::visit(const VarDeclaration* var_declaration) {

    if (checkType(var_declaration->getId()->getId())) {
        std::cout << "VarError: variable called as class " << var_declaration->getId()->getId()<<endl;
        //print_error_place(var_declaration->getPos());
    }
    var_declaration->getType()->accept(this);
}

void VisitorTypecheckerBuilder::visit(const IdType* type) {
    if (!checkType(type->getType())) {
        std::cout << "TypeError: Uknown type " << type->getType()<<endl;
        //print_error_place(type->getPos());
    }
}

void VisitorTypecheckerBuilder::visit(const MethodDeclaration* method_declaration) {
    curr_method_info_ = curr_class_info_->getMethod(method_declaration->getID()->getId());

    std::unordered_set<std::string> arg_names;
    for (const auto& type_var: method_declaration->getMethodList()->getArgList()) {
        if (arg_names.find(type_var.second->getId()) != arg_names.end()) {
            std::cout << "DefArgError: Repeted definition of argument " << type_var.second->getId()<<endl;
        }
        type_var.first->accept(this);
        arg_names.insert(type_var.second->getId());
    }
    type_stack_.push_back(method_declaration->getType()->getType());
    method_declaration->getBody()->accept(this);
}

void VisitorTypecheckerBuilder::visit(const MethodBody* method_body) {
    method_body->getExpression()->accept(this);
    std::string curr_type = type_stack_.back();
    type_stack_.pop_back();
    std::string prev_type = type_stack_.back();
    type_stack_.pop_back();
    check_and_print_invalid_type(curr_type, prev_type);

    std::unordered_set<std::string> vars;
    for (const auto& var: method_body->getVarList()->getVarList()) {
        if (vars.find(var->getId()->getId()) != vars.end()) {
            std::cout << "DefVarError: Repeted definition of variable " << var->getId()->getId()<<endl;
            //print_error_place(var->getPos());
        }
        vars.insert(var->getId()->getId());
        var->accept(this);
    }


    for (const auto& statement: method_body->getStatementList()->getStList()) {
        statement->accept(this);
    }

}

void VisitorTypecheckerBuilder::visit(const NumExpression* expr) {
    type_stack_.push_back("INT");
}
void VisitorTypecheckerBuilder::visit(const BoolExpression* expr) {
    type_stack_.push_back("Boolean");
}
void VisitorTypecheckerBuilder::visit(const IdExpression* expr) {
    if (curr_method_info_->hasVar(expr->getId())) {
        type_stack_.push_back(curr_method_info_->getVarType(expr->getId()));
    } else {
        std::cout << "DefVarError: Not defined variable " << expr->getId()<<endl;
        type_stack_.push_back("error_id_type");
    }
}
enum TOpCode {
    OC_Plus,
    OC_Mul,
    OC_And,
    OC_Minus,
    OC_Less,
};
void VisitorTypecheckerBuilder::visit(const BinopExpression* expr) {
    expr->Left()->accept(this);
    expr->Right()->accept(this);
    std::string right_type = type_stack_.back();
    type_stack_.pop_back();
    std::string left_type = type_stack_.back();
    type_stack_.pop_back();
    if (expr->OpCode() == 0|| expr->OpCode() == 3 || expr->OpCode() == 1) {
        check_and_print_invalid_type(right_type, "INT");
        check_and_print_invalid_type(left_type, "INT");
        type_stack_.push_back("INT");
    } else if (expr->OpCode() == 2) {
        check_and_print_invalid_type(right_type, "Boolean");
        check_and_print_invalid_type(left_type, "Boolean");
        type_stack_.push_back("Boolean");
    } else if (expr->OpCode() == 4) {
        check_and_print_invalid_type(right_type, "INT");
        check_and_print_invalid_type(left_type, "INT");
        type_stack_.push_back("Boolean");
    } else {
        std::cout << "DefOperatorError: Unknown operator: " << expr->OpCode()<<endl;
        //print_error_place(expr->getPos());
        assert(false);
    }
}

void VisitorTypecheckerBuilder::visit(const ExpressionSquare* expr) {
    expr->getParent()->accept(this);
    std::string curr_type = type_stack_.back();
    type_stack_.pop_back();
    check_and_print_invalid_type(curr_type, "Array");
    expr->getIndex()->accept(this);
    std::string ind_type = type_stack_.back();
    type_stack_.pop_back();
    check_and_print_invalid_type(ind_type, "INT");
    type_stack_.push_back("INT");
}

void VisitorTypecheckerBuilder::visit(const ExpressionLength* expr) {
    expr->getExpr()->accept(this);
    std::string curr_type = type_stack_.back();
    type_stack_.pop_back();
    check_and_print_invalid_type(curr_type, "Array");
    type_stack_.push_back("INT");
}

void VisitorTypecheckerBuilder::visit(const ExpressionNegation* expr) {
    expr->getExpr()->accept(this);
    std::string curr_type = type_stack_.back();
    type_stack_.pop_back();
    check_and_print_invalid_type(curr_type, "Boolean");
    type_stack_.push_back("Boolean");
}

void VisitorTypecheckerBuilder::visit(const ThisExpression* expr) {
    type_stack_.push_back(curr_class_info_->getName());
}

void VisitorTypecheckerBuilder::visit(const ExpressionNewId* expr) {
    std::string curr_type = expr->getExpr()->getId();
    if (!checkType(curr_type)) {
        std::cout << "TypeError: Uknown type " << curr_type << endl;
        //print_error_place(expr->getPos());
    }
    type_stack_.push_back(curr_type);
}
    void VisitorTypecheckerBuilder::visit(const ExpressionNewInt* expr) {
        expr->getExpr()->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(curr_type, "INT");
        type_stack_.push_back("Array");
    }

    void VisitorTypecheckerBuilder::visit(const CallExpression* expr) {
        expr->getExpr() ->accept(this);
        std::string curr_type = type_stack_.back();
        type_stack_.pop_back();
        if (!checkType(curr_type)) {
            type_stack_.push_back("error_call_type");
            return;
        }
        PClassInfo curr_class = table_->getClass(curr_type);
        std::string func_name = expr->getId()->getId();
        if (!curr_class->HasPublicFunc(func_name)) {
            std::cout << "FuncERROR: Function " << func_name << " not found in " << curr_class->getName()<<endl;
            type_stack_.push_back("error_call_type");
            return;
        }
        PMethodInfo curr_method = curr_class->getMethod(func_name);
        std::string returned_type = curr_method->getReturnType();
        if (expr->getArgs()->getArgList().size() != curr_method->getArgsNum()) {
            std::cout << "ERROR: Expected " << curr_method->getArgsNum() << " args, have " << expr->getArgs()->getArgList().size()
                      << " in function " << func_name <<" of class " << curr_type<<endl;
            type_stack_.push_back(returned_type);
            return;
        }
        for (int ind = 0; ind < static_cast<int>(expr->getArgs()->getArgList().size()); ++ind) {
            const auto& curr_arg = expr->getArgs()->getArgList()[ind];
            curr_arg->accept(this);
            std::string curr_type = type_stack_.back();
            type_stack_.pop_back();
            check_and_print_invalid_type(curr_type, curr_method->getParamType(ind));
        }
        type_stack_.push_back(returned_type);
    };

    void VisitorTypecheckerBuilder::visit(const AssignState* statement) {
        std::string id = statement->getState()->getId();
        if (curr_method_info_->hasVar(id)) {
            type_stack_.push_back(curr_method_info_->getVarType(id));
        } else {
            std::cout << "ERROR: Not defined variable " << id<<endl;
            return;
        }
        statement->getValue()->accept(this);
        std::string right_type = type_stack_.back();
        type_stack_.pop_back();
        std::string left_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(right_type, left_type);
    }

    void VisitorTypecheckerBuilder::visit(const AssignArrayState* statement) {
        std::string id = statement->getArray()->getId();
        if (!curr_method_info_->hasVar(id)) {
            std::cout << "ERROR: Not defined variable " << id<<endl;
            return;
        }
        check_and_print_invalid_type(curr_method_info_->getVarType(id), "Array");
        statement->getValue()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "INT");
        statement->getIndex()->accept(this);
        std::string ind_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(ind_type, "INT");
    };


    void VisitorTypecheckerBuilder::visit(const PrintState* statement) {
        statement->getValue()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "INT");
    };

    void VisitorTypecheckerBuilder::visit(const WhileState* statement) {
        statement->getValue()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "Boolean");
        statement->getState()->accept(this);
    };

    void VisitorTypecheckerBuilder::visit(const ConditionState* statement) {
        statement->getValue()->accept(this);
        std::string expr_type = type_stack_.back();
        type_stack_.pop_back();
        check_and_print_invalid_type(expr_type, "Boolean");
        statement->getStateIf()->accept(this);
        statement->getStateElse()->accept(this);
    };

    void VisitorTypecheckerBuilder::visit(const ObjState* statements) {
        for (const auto& statement: statements->getList()->getStList()) {
            statement->accept(this);
        }
    };

    void VisitorTypecheckerBuilder::visit(const IntType* type) { }
    void VisitorTypecheckerBuilder::visit(const BoolType* type) { };
    void VisitorTypecheckerBuilder::visit(const ArrayIntType* type) { };