#include <Visitor.h>
#include <string>
#include <vector>

class SyntaxTreePrinter : public Visitor {
public:
    virtual void visit( const NumExpression* );
    virtual void visit( const BinopExpression* );
    virtual void visit( const BoolExpression* ) ;
    virtual void visit( const IdExpression* );
    virtual void visit( const CallExpression* );
    virtual void  visit (const ExpressionLength* );
    virtual void  visit(const ExpressionSquare*);
    virtual void visit(const ExpressionNewInt*);
    virtual void visit (const ExpressionNewId*);
    virtual void visit (const ThisExpression*);
    virtual void visit (const ExpressionNegation*);
    virtual void  visit (const AssignArrayState*);
    virtual void visit (const AssignState*);
    virtual void visit (const WhileState*);

    std::string ToString() const;

private:
    static int globalIndex;
    std::string top;
    std::vector<std::string> content;
};