#include "lexer.h"

namespace moon::lexer {
    const std::unordered_map<std::string_view, lexer::token::Token::TokenType> Lexer::keywords {
        {"_int32", lexer::token::Token::TokenType::Int32},
        {"_int64", lexer::token::Token::TokenType::Int64},
        {"_float32", lexer::token::Token::TokenType::Float32},
        {"_float64", lexer::token::Token::TokenType::Float64},
        {"bool", lexer::token::Token::TokenType::Bool},
        {"if", lexer::token::Token::TokenType::kwIF},
        {"while", lexer::token::Token::TokenType::kwWHILE}, 
    };

    
} // moon::lexer