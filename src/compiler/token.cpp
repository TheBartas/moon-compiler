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
        End,
        EndOfFile,
        Comment,
        Unexpected,
    };

    Token(TokenType type, std::string_view lexeme) 
        : t_type{type}, t_lexeme{lexeme} {}

    Token(TokenType type, const char* start, size_t len)
        : t_type{type}, t_lexeme(start, len) {}

    TokenType type() const { return t_type; }
    bool is_type(TokenType type) const { return t_type == type; }
    bool is_type_of(std::initializer_list<TokenType> types) const { 
        for (auto t : types) 
            if (t_type == t) return true;
        
        return false;
    }

    std::string_view lexeme() const { return t_lexeme; }

private:
    TokenType t_type{TokenType::Unexpected};
    std::string_view t_lexeme{};
};