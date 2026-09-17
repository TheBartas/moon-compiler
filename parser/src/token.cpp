
#include "/mnt/d/Programowanie/software/C++/moon-compiler/parser/inc/token.h";

namespace moon::lexer::token {

    Token::Token(TokenType _tokenType, std::string_view _tokenLexeme) 
        : tokenType{_tokenType}, tokenLexeme{_tokenLexeme} {}

    Token::TokenType Token::getTokenType() const { return tokenType; }
    
    std::string_view Token::getTokenLexeme() const { return tokenLexeme; }

    bool Token::isTypeOf(std::initializer_list<TokenType> types) const {
        for (auto t : types) 
            if (tokenType == t) return true;
        return false;
    }

} // moon::lexer::token