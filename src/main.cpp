#include <iostream>
#include <iomanip>

#include "lexer.h"


int main() {
    auto code = "_int32 a = 23;"
                "_float32 b = 3.14.45; // This is a comment\n" 
                "a = 34 + 6;"
                "if (a > 100) {"
                "   a = a * 2;"
                "}";

    ::moon::lexer::Lexer lexer{code};

    auto tokens = lexer.tokenize();

    for (auto token : tokens) {
        std::cout << std::setw(12) << token.getTokenType() << " |" << token.getTokenLexeme() << "|\n";
    }
}