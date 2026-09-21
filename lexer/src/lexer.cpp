#include "lexer.h"

namespace moon::lexer {
    // private
    const std::unordered_map<std::string_view, lexer::token::Token::TokenType> Lexer::keywords {
        {"_int32", lexer::token::Token::TokenType::Int32},
        {"_int64", lexer::token::Token::TokenType::Int64},
        {"_float32", lexer::token::Token::TokenType::Float32},
        {"_float64", lexer::token::Token::TokenType::Float64},
        {"bool", lexer::token::Token::TokenType::Bool},
        {"if", lexer::token::Token::TokenType::kwIF},
        {"while", lexer::token::Token::TokenType::kwWHILE}, 
    };

    void Lexer::skipWhitespace() {
        while (!is_at_end() && is_whitespace(Lexer::peek())) ++pos;
    }

    lexer::token::Token Lexer::handleToken(lexer::token::Token::TokenType type) {
        return lexer::token::Token(type, std::string_view{pos++, 1});
    }

    lexer::token::Token Lexer::handleNumber() {
        const char* start = pos; 
        Lexer::advance();

        bool has_decimal = false;

        while (true) {
            if (Lexer::is_digit(Lexer::peek())) {
                Lexer::advance();
                continue;
            } 
            
            if (Lexer::peek() == '.' && !has_decimal) {
                Lexer::advance();
                has_decimal = true;
                continue;
            } 
            
            if (has_decimal) return lexer::token::Token(lexer::token::Token::TokenType::FloatLiteral, std::string_view{start, static_cast<std::size_t>(pos - start)});
            
            break;
        }

        return lexer::token::Token(lexer::token::Token::TokenType::IntegerLiteral, std::string_view{start, static_cast<std::size_t>(pos - start)});
    }

    lexer::token::Token Lexer::handleSlash() {
        const char* start = pos;
        Lexer::advance();

        if (Lexer::peek() == '/') {
            Lexer::advance();

            while (!Lexer::is_at_end()) {
                if (Lexer::peek() == '\n') break;
                Lexer::advance();
            }

            return lexer::token::Token(lexer::token::Token::TokenType::Comment, std::string_view{start, static_cast<std::size_t>(pos - start)});
        } else {
            return lexer::token::Token(lexer::token::Token::TokenType::Slash, std::string_view{start, 1});
        }
    }

    lexer::token::Token Lexer::handleIdentifier() {
        const char* start = pos;
        Lexer::advance();

        while (Lexer::is_identifier(Lexer::peek())) advance();

        const std::size_t length = pos - start;
        std::string_view lexeme(start, length);

        auto it = keywords.find(lexeme);
        if (it != keywords.end()) return lexer::token::Token(it->second, lexeme);

        return lexer::token::Token(lexer::token::Token::TokenType::Identifier, lexeme);
    }

    lexer::token::Token Lexer::next() {
        Lexer::skipWhitespace();

        if (is_at_end())
            return Lexer::handleToken(lexer::token::Token::TokenType::EndOfFile);

        char c = Lexer::peek();

        if (Lexer::is_alpha(c)) return Lexer::handleIdentifier();
        if (Lexer::is_digit(c)) return Lexer::handleNumber();

        switch (c) {
            default:
                return Lexer::handleToken(lexer::token::Token::TokenType::Unexpected);
            case '+':
                return Lexer::handleToken(lexer::token::Token::TokenType::Plus);
            case '-':
                return Lexer::handleToken(lexer::token::Token::TokenType::Minus);
            case '*':
                return Lexer::handleToken(lexer::token::Token::TokenType::Asterisk);
            case '/':
                return Lexer::handleSlash();
            case '=':
                return Lexer::handleToken(lexer::token::Token::TokenType::Equal);
            case '.':
                return Lexer::handleToken(lexer::token::Token::TokenType::Dot);
            case '(':
                return Lexer::handleToken(lexer::token::Token::TokenType::LeftParen);
            case ')':
                return Lexer::handleToken(lexer::token::Token::TokenType::RightParen);
            case '[':
                return Lexer::handleToken(lexer::token::Token::TokenType::LeftSquare);
            case ']':
                return Lexer::handleToken(lexer::token::Token::TokenType::RightSquare);
            case '{':
                return Lexer::handleToken(lexer::token::Token::TokenType::LeftCurly);
            case '}':
                return Lexer::handleToken(lexer::token::Token::TokenType::RightCurly);
            case ',':
                return Lexer::handleToken(lexer::token::Token::TokenType::Comma);
            case ';':
                return Lexer::handleToken(lexer::token::Token::TokenType::Semicolon);
            case '\'':
                return Lexer::handleToken(lexer::token::Token::TokenType::SingleQuote);
            case '"':
                return Lexer::handleToken(lexer::token::Token::TokenType::DoubleQuote);
            case '>':
                return Lexer::handleToken(lexer::token::Token::TokenType::GreaterThan);
            case '<':
                return Lexer::handleToken(lexer::token::Token::TokenType::LessThan);           
        }

        return Lexer::handleToken(lexer::token::Token::TokenType::Unexpected);
    }

    // public
    Lexer::Lexer(std::string_view _source)
        : source{_source}, pos{source.data()}, end{source.data() + source.size()} {}

    std::vector<lexer::token::Token> Lexer::tokenize() {
        std::vector<lexer::token::Token> tokens;
        for (auto token = Lexer::next(); 
            !token.isTypeOf({
                lexer::token::Token::TokenType::Unexpected, 
                lexer::token::Token::TokenType::EndOfFile
            });
            token = Lexer::next()) 
        {
            tokens.push_back(token);
        }
        return tokens;
    }
} // moon::lexer