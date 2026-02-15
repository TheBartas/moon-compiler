#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>

class Token {
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

    Token(TokenType type, std::string_view lexeme) 
        : t_type{type}, t_lexeme{lexeme} {}

    Token(TokenType type, const char* start, size_t len)
        : t_type{type}, t_lexeme(start, len) {}

    TokenType type() const { return t_type; } 
    std::string_view lexeme() const { return t_lexeme; }

    bool is_type_of(std::initializer_list<TokenType> types) const { 
        for (auto t : types) 
            if (t_type == t) return true;
    
        return false;
    }

private:
    TokenType t_type{TokenType::Unexpected};
    std::string_view t_lexeme{};
};

class Lexer {
private:
    inline char peek() const { return *l_pos; }
    inline char advance() { return *l_pos++;}

    Token token(Token::TokenType);
    Token number();
    Token create_identifier();
    Token handle_slash();

    bool is_at_end() const { return l_pos >= l_end; }
    bool is_whitespace(char c) const { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
    bool is_digit(char c) const { return c >= '0' && c <= '9'; }
    bool is_alpha(char c) const { return  (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'); }
    bool is_identifier(char c) const { return is_alpha(c) || is_digit(c); }

    void skip_whitespace() {
        while (!is_at_end() && is_whitespace(*l_pos))
            l_pos++;
    }

    const std::unordered_map<std::string_view, Token::TokenType> keywords = {
        {"_int32", Token::TokenType::Int32},
        {"_int64", Token::TokenType::Int64},
        {"_float32", Token::TokenType::Float32},
        {"_float64", Token::TokenType::Float64},
        {"bool", Token::TokenType::Bool},
        {"if", Token::TokenType::kwIF},
        {"while", Token::TokenType::kwWHILE},
    };

    const char* l_start = nullptr;
    const char* l_pos = nullptr;
    const char* l_end = nullptr;

public:
    Lexer(const char* pos)
        : l_start{pos}, l_pos{pos}, l_end{pos + std::strlen(pos)}  {}

    Lexer(std::string_view source) 
        : l_start{source.data()}, l_pos{source.data()}, l_end{source.data() + source.length()} {}

    std::vector<Token> tokenize();
    Token next();
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
    skip_whitespace();

    if (is_at_end())
        return token(Token::TokenType::EndOfFile);

    char c = peek();

    if (is_alpha(c)) return create_identifier();
    if (is_digit(c)) return number();

    switch (c)
    {
        default:
            return token(Token::TokenType::Unexpected);
        case '+':
            return token(Token::TokenType::Plus);
        case '-':
            return token(Token::TokenType::Minus);
        case '*':
            return token(Token::TokenType::Asterisk);
        case '/':
            return handle_slash();
        case '=':
            return token(Token::TokenType::Equal);
        case '.':
            return token(Token::TokenType::Dot);
        case '(':
            return token(Token::TokenType::LeftParen);
        case ')':
            return token(Token::TokenType::RightParen);
        case '[':
            return token(Token::TokenType::LeftSquare);
        case ']':
            return token(Token::TokenType::RightSquare);
        case '{':
            return token(Token::TokenType::LeftCurly);
        case '}':
            return token(Token::TokenType::RightCurly);
        case ',':
            return token(Token::TokenType::Comma);
        case ';':
            return token(Token::TokenType::Semicolon);
        case '\'':
            return token(Token::TokenType::SingleQuote);
        case '"':
            return token(Token::TokenType::DoubleQuote);
        case '>':
            return token(Token::TokenType::GreaterThan);
        case '<':
            return token(Token::TokenType::LessThan);
    }
    
    return token(Token::TokenType::Unexpected);
}

Token Lexer::number() {
    const char* start = l_pos;
    advance();

    bool has_decimal = false;

    while(is_digit(peek()) || peek()=='.') {
        if (peek() == '.') {
            if (has_decimal) return Token(Token::TokenType::FloatLiteral, start, l_pos - start);
            has_decimal = true;
        }
        advance();
    }

    return Token(Token::TokenType::IntegerLiteral, start, l_pos - start);
}

Token Lexer::create_identifier() {
    const char* start = l_pos;
    advance();
    while (is_identifier(peek())) advance();

    size_t length = l_pos - start;

    std::string_view lexeme(start, length);

    auto it = keywords.find(lexeme);
    if (it != keywords.end()) {
        return Token(it->second, lexeme);
    }

    return Token(Token::TokenType::Identifier, lexeme);
}

Token Lexer::handle_slash() {
    const char* start = l_pos;
    advance();

    if (peek() == '/') {
        advance();
        start = l_pos;

        while (!is_at_end()) {
            if (peek() == '\n') break;
            advance();
        }

        return Token(Token::TokenType::Comment, start, l_pos - start);
    } else {
        return Token(Token::TokenType::Slash, start, 1);
    }
}


std::ostream& operator<<(std::ostream& os, const Token::TokenType& type) {
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


int main() {
    auto code = "_int32 a = 23;"
                "_float32 b = 3.14.45; // This is a comment\n" 
                "a = 34 + 6;"
                "if (a > 100) {"
                "   a = a * 2;"
                "}";

    Lexer lexer(code);

    auto tokens = lexer.tokenize();

    for (auto token : tokens) {
        std::cout << std::setw(12) << token.type() << " |" << token.lexeme() << "|\n";
    }
}



