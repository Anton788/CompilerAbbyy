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
    string opCode = e->OpCode() == BinopExpression::OC_Plus ? "PLUS" : "MUL";

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
    std::vector<std::string> namesChild;
    for (auto value : e->getArgs()->getArgList()) {
        value->accept(this);
        namesChild.push_back(top);
    }
    int topIndex = globalIndex++;
    top = to_string(topIndex);
    content.push_back(top + "[label=Call ordering=out];");

    int opIndex = globalIndex++;
    string opStr = to_string(opIndex);
    for (auto value :namesChild) {
        content.push_back(top + "->" + value + ";");
    }

}

string SyntaxTreePrinter::ToString() const
{
    stringstream ss;
    ss << "digraph G {" << endl;
    for_each( content.begin(), content.end(), [&]( const string& i ) { ss << i << endl; } );
    ss << "}";

    return ss.str();
}