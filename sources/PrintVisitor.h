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

    std::string ToString() const;

private:
    static int globalIndex;
    std::string top;
    std::vector<std::string> content;
};