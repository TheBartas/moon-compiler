#include <iostream>
#include <iomanip>

#include "lexer.h"
#include "parser.h"


int main() {
    auto code = "_int32 a = 23;"
                "_float32 b = 3.14.45; // This is a comment\n" 
                "a = 34 + 6;"
                "if (a > 100) {"
                "   a = a * 2;"
                "}";
    
    auto code2 = "_int32 a = 23;";


    // Lexer

    ::moon::lexer::Lexer lexer{code2};

    auto tokens = lexer.tokenize();

    for (auto token : tokens) {
        std::cout << std::setw(12) << token.getTokenType() << " |" << token.getTokenLexeme() << "|\n";
    }

    // Parser

    ::moon::parser::Parser parser{tokens};

    parser.parse();
}