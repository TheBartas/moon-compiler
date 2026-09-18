#include <iostream>
#include <iomanip>

int main() {
    auto code = "_int32 a = 23;"
                "_float32 b = 3.14.45; // This is a comment\n" 
                "a = 34 + 6;"
                "if (a > 100) {"
                "   a = a * 2;"
                "}";

    moon::token::Lexer lexer(code);

    auto tokens = lexer.tokenize();

    for (auto token : tokens) {
        std::cout << std::setw(12) << token.type() << " |" << token.lexeme() << "|\n";
    }
}