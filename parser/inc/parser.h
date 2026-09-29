#ifndef MOON_PARSER_H
#define MOON_PARSER_H

#include <vector>
#include "lexer.h"

namespace moon::parser {

    using AToken = ::moon::lexer::token::Token; // Aliases should always begin with the letter 'A'

    class Parser final {
    private:
        std::size_t current{};
        std::vector<::moon::lexer::token::Token> tokens{};

        inline const AToken& peek() const { return tokens[current]; }; // Return current token
        inline const AToken& advance() { return tokens[current++]; }; // Return current token and move to the next one
        inline bool check(AToken::TokenType type) const { return tokens[current].getTokenType() == type; }; // Check if current token is the same as the expected
        // inline bool match(AToken::TokenType); // Check if current token is the same as the expected and consume it
        const AToken& consume(AToken::TokenType type) {
            if (Parser::check(type)) {
                return tokens[current++];
            }
            return tokens[current++]; // Temporary solution TODO: add throw
        }; // Check if current token is the same as the expected and consume it. Otherwise, it throws an exception.

        inline bool is_at_end() const { return tokens[current].getTokenType() == AToken::TokenType::EndOfFile; }



// TODO: add AST:
        void parseProgram();

        // Recursive Descent Parser 
        void parseStmt(); 
        void parseExprAssign();

        // Pratt


    public:
        explicit Parser(std::vector<AToken>&);

        void parse();
    };
} // namespace moon::parser



#endif