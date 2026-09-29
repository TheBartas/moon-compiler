#include "parser.h"
#include <iostream>

namespace moon::parser
{
    // private
    void Parser::parseProgram() {
        while (!Parser::is_at_end()) {
            Parser::parseStmt();
        }
    }

    void Parser::parseStmt() {
        auto token = Parser::peek();
        switch (token.getTokenType()) {
            case AToken::TokenType::Int32:
            case AToken::TokenType::Float32:
                Parser::parseExprAssign();
                break;
            default:
                break;
        }
    }

    void Parser::parseExprAssign() {
        (void)Parser::consume(AToken::TokenType::Identifier);
        (void)Parser::consume(AToken::TokenType::Equal);
        std::cout << tokens[current].getTokenType() << std::endl;
        // TODO: handle expr
        (void)Parser::consume(AToken::TokenType::IntegerLiteral);
        std::cout << tokens[current].getTokenType() << std::endl;
        (void)Parser::consume(AToken::TokenType::Semicolon);
        std::cout << tokens[current].getTokenType() << std::endl;
        current++;
    }

    // public
    Parser::Parser(std::vector<AToken>& _tokens) 
        : tokens{_tokens} {}


    void Parser::parse() {
        // TODO: add try..catch to catch exceptions (need to add ErrorHandlingClass)
        Parser::parseProgram();
    }
} // namespace moon::parser
