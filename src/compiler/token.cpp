#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

class Token {
public:
    enum class TokenType {
        Identifier,
        IntegerLiteral,
        FloatLiteral,
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
        Dot,
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



class Lexer {
public:
    Lexer(const char* pos)
        : l_pos{pos} {}

    std::vector<Token> tokenize();

    std::unordered_map<Token::TokenType, std::string> keywords1 = { // public for tests only
        {Token::TokenType::Identifier, "Identifier"},
        {Token::TokenType::Int32, "_int32"},
        {Token::TokenType::Equal, "Equal"},
    };

private:
    Token next();
    Token token(Token::TokenType);
    Token create_number();
    Token create_identifier();

    bool is_whitespace(char c) const { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
    bool is_digit(char c) const { return c >= '0' && c <= '9'; }
    bool is_alpha(char c) const { return  (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'); }
    bool is_identifier(char c) const {
        return is_alpha(c) || is_digit(c);
    }

    const std::unordered_map<std::string_view, Token::TokenType> keywords = {
        {"_int32", Token::TokenType::Int32},
        {"_int64", Token::TokenType::Int64},
        {"_float32", Token::TokenType::Float32},
        {"_float64", Token::TokenType::Float64},
        {"bool", Token::TokenType::Bool},
    };

    const char* l_pos = nullptr;
};

Token Lexer::token(Token::TokenType type) { return Token(type, l_pos++,1); }

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    for (auto token = next(); 
        !token.is_type_of({Token::TokenType::Unexpected, Token::TokenType::EndOfFile});
        token = next()) 
    {
        tokens.push_back(token);
    }

    return tokens;
}

Token Lexer::next() {
    while(is_whitespace(*l_pos)) *l_pos++;

    if (is_alpha(*l_pos)) return create_identifier();
    else if (is_digit(*l_pos)) return create_number();
    else {
        switch (*l_pos)
        {
            default:
                return token(Token::TokenType::Unexpected);
            case '=':
                return token(Token::TokenType::Equal);
        }
    }

    return token(Token::TokenType::Unexpected);
}

Token Lexer::create_number() {
    const char* start = l_pos;
    *l_pos++;

    bool has_decimal = false;

    while(is_digit(*l_pos) || *l_pos=='.') *l_pos++;

    return token(Token::TokenType::Unexpected);
}

Token Lexer::create_identifier() {
    const char* start = l_pos;
    l_pos++;
    while (is_identifier(*l_pos)) l_pos++;

    size_t length = std::distance(start, l_pos);

    std::string_view lexeme(start, length);

    auto it = keywords.find(lexeme);
    if (it != keywords.end()) {
        return Token(it->second, lexeme);
    }

    return Token(Token::TokenType::Identifier, lexeme);
}


int main() {
    auto code = "_int32 a = ";

    Lexer lexer(code);

    auto tokens = lexer.tokenize();

    for (auto token : tokens) {
        std::cout << std::setw(12) << lexer.keywords1[token.type()] << " |" << token.lexeme() << "|\n";
    }
}



