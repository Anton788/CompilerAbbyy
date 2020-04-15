#include <Visitor.h>
#include <SyntaxTree.h>
#include <iostream>
#include <assert.h>

using namespace std;

void CompVisitor::visit( const NumExpression* e )
{
    assert( e != 0 );
    subtreeValue = e->Value();
}

void CompVisitor::visit( const BinopExpression* e )
{
    assert( e != 0 );

    e->Left()->accept( this );
    int left = subtreeValue;

    e->Right()->accept( this );
    int right = subtreeValue;

    switch( e->OpCode() ) {
        case BinopExpression::OC_Plus:
            subtreeValue = left + right;
            break;
        case BinopExpression::OC_Mul:
            subtreeValue = left * right;
            break;
        case BinopExpression::OC_Minus:
            subtreeValue = left - right;
            break;
        case BinopExpression::OC_And:
            subtreeValue = left && right;
            break;
        case BinopExpression::OC_Less:
            subtreeValue = left < right;
            break;

        default:
            cerr << "Unknown operation" << endl;
    }
}

void CompVisitor::visit( const BoolExpression* e )
{
    assert( e != 0 );
    subtreeValue = e->Value();
}

void CompVisitor::visit( const ThisExpression* e )
{
    assert( e != 0 );
    subtreeValue = e->Value();
}