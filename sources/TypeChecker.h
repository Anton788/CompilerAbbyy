#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <memory>

#include <SyntaxTree.h>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "SymbolTable.hpp"
#include "SyntaxTree.h"
#include <Visitor.h>



class VisitorTypecheckerBuilder: public Visitor{
    public:
        explicit VisitorTypecheckerBuilder(PTableGlobal symb_table) :
                table_(symb_table)
        { }
        void check_and_print_invalid_type(const std::string& curr_type,
                                          const std::string& expected_type) {
            if (!CompareTypes(expected_type, curr_type)) {
                std::cout << "TypeError: Wrong type: " << curr_type <<",  expected: " << expected_type;
                throw 1;
                //return;
            }
        }

        bool check_errors() const { return no_mistakes_; }


private:
        bool no_mistakes_ = true;
        bool curr_expr_may_be_lvalue = false;
        std::shared_ptr<TableGlobal> table_;
        std::unordered_set<std::string> types_;
        std::vector<std::string> type_stack_;
        PClassInfo curr_class_info_;
        PMethodInfo curr_method_info_;

    void visit(const NumExpression* expr);
    void visit(const BinopExpression* expr);
    void visit(const BoolExpression* expr);
    void visit(const IdExpression* expr);
    void visit(const ExpressionSquare* expr);
    void visit(const ExpressionLength* expr);
    void visit(const ExpressionNegation* expr);
    void visit(const ThisExpression* expr);
    void visit(const AssignState* statement);
    void visit(const IntType* type);
    void visit(const BoolType* type);
    void visit(const ArrayIntType* type);
    void visit(const IdType* type);
    void visit(const VarDeclaration* var_declaration);
    void visit(const MethodBody* method_body);
    void visit(const MethodDeclaration* method_declaration);
    void visit(const ClassDeclaration* class_var);
    void visit(const MainClass* main_class);
    void visit(const Goal* goal);
    void visit(const ExpressionNewId* expr);
    void visit(const ExpressionNewInt* expr);
    void visit(const CallExpression* expr);
    void visit(const AssignArrayState* statement);
    void visit(const PrintState* statement);
    void visit(const WhileState* statement);
    void visit(const ConditionState* statement);
    void visit(const ObjState* statement);
        bool DFScheckCycle(const std::unordered_map<std::string, std::vector<std::string> >& graph,  const std::string& vert,
                           std::unordered_map<std::string, int>& used) const {
            used[vert] = 1;
            if (graph.find(vert) == graph.end()) {
                used[vert] = 2;
                return true;
            }
            for (const auto& chld: graph.at(vert)) {
                if (used[chld] == 2) {
                    continue;
                }
                if (used[chld] == 1) {
                    std::cout << "RuntimeError:  dependecies cycle : " <<chld <<" -> " << vert;
                    //return false;
                    throw 1;
                    //return;
                }
                if (!DFScheckCycle(graph, chld, used)) {
                    std::cout <<" -> "<< vert;
                    return false;
                }
            }
            used[vert] = 2;
            return true;
        }

        bool checkCycle() {
            std::unordered_map<std::string, int> used;
            const std::unordered_map<std::string, std::vector<std::string> >& graph = table_->getGraph();
            for (const auto& vert: graph) {
                if (used[vert.first] == 0) {
                    if (!DFScheckCycle(graph, vert.first, used)) {
                        std::cout << "\n";
                        no_mistakes_ = false;
                        return false;
                    }
                }
            }
            return true;
        }

        void initTypes() {
            for (const auto& vert: table_->getClasses()) {
                types_.insert(vert.first);
            }
        }

        bool checkType(const std::string& type) const {
            return types_.find(type) != types_.end();
        }

        bool hasChild(const std::string& parent, const std::string& chld) const {
            if (parent == chld) {
                return true;
            }
            const std::unordered_map<std::string, std::vector<std::string> >& graph = table_->getGraph();
            if (graph.find(parent) == graph.end()) {
                return false;
            }
            for (const auto& vert: graph.at(parent)) {
                if (hasChild(vert, chld)) {
                    return true;
                }
            }
            return false;
        }

        void AddParentClassesForClass(PClassInfo& pclass) {
            if (pclass->getParent() != "") {
                AddParentClassesForClass(table_->getClass(pclass->getParent()));
                pclass->addParentClass(table_->getClass(pclass->getParent()));
            }
        }

        void AddParentClasses() {
            for (auto& pclass : table_->getClasses()) {
                AddParentClassesForClass(table_->getClass(pclass.first));
            }
        }
        bool CompareTypes(const std::string& const_type, const std::string& type_may_be_casted) const {
            if (const_type == type_may_be_casted) {
                return true;
            }
            if (!checkType(const_type) || !checkType(type_may_be_casted)) {
                return false;
            }
            return hasChild(const_type, type_may_be_casted);
        }

    };