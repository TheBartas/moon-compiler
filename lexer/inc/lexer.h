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
        const char* pos{};
        const char* end{};

        static const std::unordered_map<std::string_view, lexer::token::Token::TokenType> keywords;

        inline char peek() const { return *pos; };
        inline char advance() { return *pos++; };

        inline bool is_at_end() const { return pos >= end; }
        inline bool is_whitespace(char c) const { return c == ' ' || c == '\n' || c == '\t'; }
        inline bool is_digit(char c) const { return c >= '0' && c <= '9'; }
        inline bool is_alpha(char c) const { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'); }
        inline bool is_identifier(char c) const { return is_alpha(c) || is_digit(c); }

        void skipWhitespace();

        lexer::token::Token handleToken(lexer::token::Token::TokenType);
        lexer::token::Token handleNumber();
        lexer::token::Token handleSlash();
        lexer::token::Token handleIdentifier();

        lexer::token::Token next();

    public:
        explicit Lexer(std::string_view);

        std::vector<lexer::token::Token> tokenize();
    };
} // namespace moon::lexer

#endif