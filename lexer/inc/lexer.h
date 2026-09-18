#ifndef MOON_LEXER_H
#define MOON_LEXER_H

#include <vector>
#include <unordered_map>
#include <string_view>
#include "token.h"

namespace moon::lexer {
    class Lexer final {
    private:
        std::string_view source{};
        std::size_t pos{};

        static const std::unordered_map<std::string_view, lexer::token::Token::TokenType> keywords;

        inline char peek() const { return pos; };
        inline char advance() { return source[pos++]; };

        bool is_at_end() const { return pos >= source.size(); }
        bool is_whitespace(char) const;
        bool is_digit(char) const;
        bool is_alpha(char) const;
        bool is_identifier(char) const;

        void skipWhitespace();

        lexer::token::Token next();

        lexer::token::Token handleToken(lexer::token::Token::TokenType);
        lexer::token::Token handleNumber();
        lexer::token::Token handleSlash();
        lexer::token::Token handleIdentifier();

    public:
        explicit Lexer(std::string_view);

        std::vector<lexer::token::Token> tokenize();
    };
} // namespace moon::lexer

#endif