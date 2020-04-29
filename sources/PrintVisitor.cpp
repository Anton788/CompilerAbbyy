#include <PrintVisitor.h>
#include <SyntaxTree.h>
#include <sstream>
#include <algorithm>

using namespace std;

// static
int SyntaxTreePrinter::globalIndex = 0;

void SyntaxTreePrinter::visit( const NumExpression* e )
{
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=NumExp];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + to_string(e->Value() ) + "];" );

    content.push_back( top + "->" + numStr + ";" );
}

void SyntaxTreePrinter::visit(const ExpressionNewInt* e) {
    e->getExpr()->accept(this);
    string expr = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ExprNewInt];" );
    content.push_back( top + "->" + expr + ";" );
}

void SyntaxTreePrinter::visit(const ThisExpression* e) {
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ThisExpr];" );
    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + "This" + "];" );
    content.push_back( top + "->" + numStr + ";" );
}

void SyntaxTreePrinter::visit(const ExpressionNegation* e) {
    e->getExpr()->accept(this);
    string expr = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ExprNeg];" );
    content.push_back( top + "->" + expr + ";" );
}

void SyntaxTreePrinter::visit(const ExpressionNewId* e) {
    e->getExpr()->accept(this);
    string expr = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ExprNewId];" );
    content.push_back( top + "->" + expr + ";" );
}


void SyntaxTreePrinter::visit(const ExpressionSquare* e) {
    e->getParent()->accept(this);
    string parent = top;
    e->getIndex()->accept(this);
    string index = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=SquareExp];" );
    content.push_back( top + "->" + parent + ";" );
    content.push_back(top + "->" + index + ";");
}

void SyntaxTreePrinter::visit(const ExpressionLength* e){
    e->getExpr()->accept(this);
    string branch = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=LengthExp];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + "Length" + " color=blue " + "];" );
    content.push_back( top + "->" + numStr + ";" );
    content.push_back(top + "->" + branch + ";");
}

void SyntaxTreePrinter::visit( const BinopExpression* e )
{
    e->Left()->accept( this );
    string left = top;

    e->Right()->accept( this );
    string right = top;

    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=BinOp ordering=out];" );

    int opIndex = globalIndex++;
    string opStr = to_string( opIndex );
    string opCode;
    if ( e->OpCode() == BinopExpression::OC_Plus){
        opCode = "PLUS";
    }
    if ( e->OpCode() == BinopExpression::OC_Mul){
        opCode = "MUL";
    }
    if (e->OpCode() == BinopExpression::OC_And){
        opCode = "AND";
    }
    if (e->OpCode() == BinopExpression::OC_Minus){
        opCode="MINUS";
    }
    if (e->OpCode() == BinopExpression::OC_Less) {
        opCode = "LESS";
    }
    content.push_back( opStr + "[label=" + opCode + " color=blue];" );

    content.push_back( top + "->" + left + ";" );
    content.push_back( top + "->" + opStr + ";" );
    content.push_back( top + "->" + right + ";" );

}
 void SyntaxTreePrinter::visit( const BoolExpression* e){

     int topIndex = globalIndex++;
     top = to_string( topIndex );
     content.push_back( top + "[label=BoolExp];" );

     int numIndex = globalIndex++;
     string numStr = to_string( numIndex );
     content.push_back( numStr + "[label=" + to_string(e->Value()) + "];" );

     content.push_back( top + "->" + numStr + ";" );
}
void SyntaxTreePrinter::visit( const IdExpression* e){

    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=IdExp];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + e->getId() + "];" );

    content.push_back( top + "->" + numStr + ";" );
}
void SyntaxTreePrinter::visit( const CallExpression* e) {
    e->getExpr()->accept(this);
    std::string my_class = top;

    std::vector<std::string> namesChild;
    for (auto value : e->getArgs()->getArgList()) {
        value->accept(this);
        namesChild.push_back(top);
    }
    int topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string arguments = top;
    content.push_back(top + "[label=Arguments " + "ordering=out];");

    for (auto value :namesChild) {
        content.push_back(top + "->" + value + ";");
    }

    topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string id = top;
    content.push_back(top + "[label=" + e->getId() + " ];");


    topIndex = globalIndex++;
    top = to_string(topIndex);
    content.push_back(top + "[label=CallExpr" + " ];");
    content.push_back(top + "->" + my_class + ";");
    content.push_back(top + "->" + id + ";");
    content.push_back(top + "->" + arguments + ";");


}

void SyntaxTreePrinter::visit( const AssignArrayState* e){
    e->getIndex()->accept(this);
    string index = top;
    e->getValue()->accept(this);
    string value = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=AssignArrayState];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + e->getArray() + "];" );

    content.push_back( top + "->" + numStr + ";" );
    content.push_back( top + "->" + index + ";" );
    content.push_back( top + "->" + value + ";" );
}

void SyntaxTreePrinter::visit( const AssignState* e){
    e->getValue()->accept(this);
    string value = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=AssignState];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + e->getState() + "];" );

    content.push_back( top + "->" + numStr + ";" );
    content.push_back( top + "->" + value + ";" );
}

void SyntaxTreePrinter::visit( const WhileState* e){
    e->getValue()->accept(this);
    string value = top;
    e->getState()->accept(this);
    string state = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=WhileState];" );
    content.push_back( top + "->" + state + ";" );
    content.push_back( top + "->" + value + ";" );
}


void SyntaxTreePrinter::visit( const ObjState* e) {
    //e->accept(this);
    std::string my_class = top;

    std::vector<std::string> namesChild;
    for (auto value : e->getList()->getStList()) {
        value->accept(this);
        namesChild.push_back(top);
    }
    int topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string arguments = top;
    content.push_back(top + "[label=ArgState " + "ordering=out];");

    for (auto value :namesChild) {
        content.push_back(top + "->" + value + ";");
    }
    topIndex = globalIndex++;
    top = to_string(topIndex);
    content.push_back(top + "[label=ObjState" + " ];");
    content.push_back(top + "->" + arguments + ";");
}

void SyntaxTreePrinter::visit( const PrintState* e){
    e->getValue()->accept(this);
    string value = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=PrintState];" );
    content.push_back( top + "->" + value + ";" );
}


string SyntaxTreePrinter::ToString() const
{
    stringstream ss;
    ss << "digraph G {" << endl;
    for_each( content.begin(), content.end(), [&]( const string& i ) { ss << i << endl; } );
    ss << "}";

    return ss.str();
}


void SyntaxTreePrinter::visit( const ConditionState* e){
    e->getStateIf()->accept(this);
    string state_if = top;
    e->getStateElse()->accept(this);
    string state_else = top;
    e->getValue()->accept(this);
    string value = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ConditionState];" );
    content.push_back( top + "->" + value + ";" );
    content.push_back( top + "->" + state_if + ";" );
    content.push_back( top + "->" + state_else + ";" );
}

void SyntaxTreePrinter::visit( const ArrayIntType* e){
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=ArrayIntType];" );
}

void SyntaxTreePrinter::visit( const BoolType* e){
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=BoolType];" );
}

void SyntaxTreePrinter::visit( const IntType* e){
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=IntType];" );
}

void SyntaxTreePrinter::visit( const IdType* e){
    e->getValue()->accept(this);
    string value = top;
    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=IntType];" );
    content.push_back( top + "->" + value + ";" );
}



void SyntaxTreePrinter::visit(const VarDeclaration* e) {
    e->getType()->accept(this);
    string type = top;

    int topIndex = globalIndex++;
    top = to_string( topIndex );
    content.push_back( top + "[label=VarDec];" );

    int numIndex = globalIndex++;
    string numStr = to_string( numIndex );
    content.push_back( numStr + "[label=" + e->getId() + "];" );

    content.push_back( top + "->" + numStr + ";" );
    content.push_back( top + "->" + type + ";" );
}

void SyntaxTreePrinter::visit( const MethodBody* e) {
    e->getExpression()->accept(this);
    std::string my_class = top;

    std::vector<std::string> varList;
    for (auto value : e->getVarList()->getVarList()) {
        value->accept(this);
        varList.push_back(top);
    }
    int topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string arguments = top;
    content.push_back(top + "[label=VarArg " + "ordering=out];");

    for (auto value :varList) {
        content.push_back(top + "->" + value + ";");
    }


    std::vector<std::string> stList;
    for (auto value : e->getStatementList()->getStList()) {
        value->accept(this);
        stList.push_back(top);
    }
    topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string argState = top;
    content.push_back(top + "[label=ArgState " + "ordering=out];");

    for (auto value :stList) {
        content.push_back(top + "->" + value + ";");
    }

    topIndex = globalIndex++;
    top = to_string(topIndex);
    content.push_back(top + "[label=Body" + " ];");
    content.push_back(top + "->" + my_class + ";");
    content.push_back(top + "->" + argState + ";");
    content.push_back(top + "->" + arguments + ";");
}


void SyntaxTreePrinter::visit( const MethodDeclaration* e) {
    e->getBody()->accept(this);
    std::string my_class = top;
    e->getType()->accept(this);
    std::string type_top=top;

    std::vector<std::string> Args;
    for (auto value : e->getMethodList()->getArgList()) {
        value.first->accept(this);
        Args.push_back(top);
        //value.second

    }
    int topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string arguments = top;
    content.push_back(top + "[label=MetArg " + "ordering=out];");

    for (auto value :Args) {
        content.push_back(top + "->" + value + ";");
    }

    topIndex = globalIndex++;
    top = to_string(topIndex);
    std::string id = top;
    content.push_back(top + "[label=" + e->getID()+ " ];");


    topIndex = globalIndex++;
    top = to_string(topIndex);
    content.push_back(top + "[label=MetDecl" + " ];");
    content.push_back(top + "->" + my_class + ";");
    content.push_back(top + "->" + id + ";");
    content.push_back(top + "->" + type_top + ";");
    content.push_back(top + "->" + arguments + ";");
}
