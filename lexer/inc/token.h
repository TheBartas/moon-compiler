#ifndef MOON_LEXER_TOKEN_H
#define MOON_LEXER_TOKEN_H

#include <iostream>
#include <string_view>
#include <initializer_list>


namespace moon::lexer::token {
    class Token final {
    public:
        enum class TokenType {
            Identifier,
            IntegerLiteral,
            FloatLiteral,
            Plus,
            Minus,
            Asterisk,
            Slash,
            Equal,
            Dot,
            LeftParen,
            RightParen,
            LeftSquare,
            RightSquare,
            LeftCurly,
            RightCurly,
            Comma,
            Semicolon,
            SingleQuote,
            DoubleQuote,
            LessThan,
            GreaterThan,
            End,
            EndOfFile,
            Comment,
            Unexpected,
    // keywords
            Int32,
            Int64,
            Float32,
            Float64,
            Bool,
            kwIF,
            kwWHILE,
        };

        Token(TokenType, std::string_view);

        TokenType getTokenType() const;
        std::string_view getTokenLexeme() const;
        bool isTypeOf(std::initializer_list<TokenType>) const;

    private:
        TokenType tokenType{TokenType::Unexpected};
        std::string_view tokenLexeme{};
    };  
} // namespace moon::lexer::token


#endif