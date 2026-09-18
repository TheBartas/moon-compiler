add_library(Lexer
    src/lexer.cpp 
    src/token.cpp
)

target_include_directories(Lexer PUBLIC inc)