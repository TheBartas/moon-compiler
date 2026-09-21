#ifndef MOON_LEXER_TOKEN_H
#define MOON_LEXER_TOKEN_H

#include <iostream>
#include <string_view>
#include <initializer_list>
#include <ostream>


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

        // [TODO] Replace with Printable class type
        friend std::ostream& operator<<(std::ostream& os, const lexer::token::Token::TokenType& type) {
            switch (type)
            {
                case Token::TokenType::Identifier: return os << "Identifier";
                case Token::TokenType::IntegerLiteral: return os << "Integer";
                case Token::TokenType::FloatLiteral: return os << "Float";
                case Token::TokenType::Plus: return os << "Plus";
                case Token::TokenType::Minus: return os << "Minus";
                case Token::TokenType::Asterisk: return os << "Asterisk";
                case Token::TokenType::Slash: return os << "Slash";
                case Token::TokenType::Equal: return os << "Equal";
                case Token::TokenType::Dot: return os << "Dot";
                case Token::TokenType::LeftParen: return os << "LeftParen";
                case Token::TokenType::RightParen: return os << "RightParen";
                case Token::TokenType::LeftSquare: return os << "LeftSquare";
                case Token::TokenType::RightSquare: return os << "RightSquare";
                case Token::TokenType::LeftCurly: return os << "LeftCurly";
                case Token::TokenType::RightCurly: return os << "RightCurly";
                case Token::TokenType::Comma: return os << "Comma";
                case Token::TokenType::Semicolon: return os << "Semicolon";
                case Token::TokenType::SingleQuote: return os << "SingleQuote";
                case Token::TokenType::DoubleQuote: return os << "DoubleQuote";
                case Token::TokenType::LessThan: return os << "LessThan";
                case Token::TokenType::GreaterThan: return os << "GreaterThan";
                case Token::TokenType::End: return os << "End";
                case Token::TokenType::EndOfFile: return os << "EndOfFile";
                case Token::TokenType::Comment: return os << "Comment";
                case Token::TokenType::Unexpected: return os << "Unexpected";
                case Token::TokenType::Int32: return os << "_int32";
                case Token::TokenType::Float32: return os << "_float32";
                case Token::TokenType::kwIF: return os << "Keyword_IF";
                case Token::TokenType::kwWHILE: return os << "Keyword_WHILE";
            }

            return os << "Unknown";
        }

    private:
        TokenType tokenType{TokenType::Unexpected};
        std::string_view tokenLexeme{};
    };  
} // namespace moon::lexer::token


#endif