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

        const AToken& peek() const; // Return current token
        const AToken& peek(std::size_t) const; // Return token by ID
        const AToken& advance(); // Return current token and move to the next one
        bool check(AToken::TokenType) const; // Check if current token is the same as the expected
        bool match(AToken::TokenType); // Check if current token is the same as the expected and consume it
        const AToken& consume(AToken::TokenType); // Check if current token is the same as the expected and consume it. Otherwise, it throws an exception.


    public:
        explicit Parser(std::vector<::moon::lexer::token::Token>&);

        void parse();
    };
} // namespace moon::parser



#endif