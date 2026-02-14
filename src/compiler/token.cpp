#include <string>
#include <iostream>

class Token {
public:
    enum class TokenType {
        Identifier,
        Number,
        Int32,
        Int64,
        Float32,
        Float64,
        Bool,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Equal,
        Semicolon,
        SingleQuote,
        DoubleQuote,
        Comment,
        Unexpected,
    };

    Token(TokenType type, std::string lexeme, int line, int column)
        : _type{type}, _lexeme{std::move(lexeme)}, _line{line}, _column{column} {}

    TokenType type() const { return _type; }
    const std::string& lexeme() const { return _lexeme; }
    int line() const { return _line; }
    int column() const { return _column; }

private:
    TokenType _type{TokenType::Unexpected};
    std::string _lexeme{};
    int _line{0};
    int _column{0};
};