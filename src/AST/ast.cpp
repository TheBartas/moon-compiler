#include <iostream>
#include <memory>


class ASTNode;
class NumberNode;
class IdentifierNode;
class KeywordNode;
class BinaryExpressionNode;


using ASTNodePtr = std::unique_ptr<ASTNode>;


class ASTVisitor {
public:
    virtual void visit(NumberNode &node) = 0;
    virtual void visit(IdentifierNode &node) = 0;
    virtual void visit(BinaryExpressionNode &node) = 0;
};


struct SourceLocation {
    int line;
    int column;
};

class ASTNode {
public:
    SourceLocation location;

    virtual void accept(ASTVisitor &visitor) = 0;
    virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode {
public:
    std::string value;
    NumberNode(const std::string_view value) : value(value) {}
    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class IdentifierNode : public ASTNode {
public:
    std::string name;
    IdentifierNode(const std::string_view name) : name(name) {}
    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class BinaryExpressionNode : public ASTNode {
public:
    std::string op;
    ASTNodePtr left;
    ASTNodePtr right;

    BinaryExpressionNode(
        const std::string_view op, 
        std::unique_ptr<ASTNode> left, 
        std::unique_ptr<ASTNode> right) :
        op(std::move(op)), left(std::move(left)), right(std::move(right)) {}
    void accept(ASTVisitor &visitor) override { visitor.visit(*this); }
};

class ASTVisitorPrinter : public ASTVisitor {
public: 
    void visit(NumberNode &node) override { std::cout << node.value; }
    void visit(IdentifierNode &node) override { std::cout << node.name; }
    void visit(BinaryExpressionNode &node) override { 
        std::cout << "(";
        node.left->accept(*this);
        std::cout << " " << node.op << " ";
        node.right->accept(*this);
        std::cout << ")";
    }
};

int main() {
    // 34 + a * 10 - beta
    auto mul = std::make_unique<BinaryExpressionNode>(
        "*", 
        std::make_unique<IdentifierNode>("a"),
        std::make_unique<NumberNode>("10")
    );

    auto minus = std::make_unique<BinaryExpressionNode>(
        "-",
        std::move(mul),
        std::make_unique<IdentifierNode>("beta")
    );

    auto program = std::make_unique<BinaryExpressionNode>(
        "+",
        std::make_unique<NumberNode>("34"),
        std::move(minus)
    );

    ASTVisitorPrinter printer;
    program->accept(printer);
}



