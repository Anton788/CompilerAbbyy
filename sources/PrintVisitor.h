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
    virtual void visit (const ObjState*);
    virtual void visit (const PrintState*);
    virtual void visit (const ConditionState*);
    virtual void visit (const ArrayIntType*);
    virtual void visit (const BoolType*);
    virtual void visit (const IntType*);
    virtual void visit (const IdType*);
    virtual void visit (const VarDeclaration*);
    virtual void visit (const MethodBody*);
    virtual void visit (const MethodDeclaration*);
    virtual void visit (const ClassDeclaration*);
    virtual void visit (const MainClass*);
    virtual void visit (const Goal*);

    std::string ToString() const;

private:
    static int globalIndex;
    std::string top;
    std::vector<std::string> content;
};