cmake_minimum_required(VERSION 3.20)

project(MoonCompiler LANGUAGES CXX)

add_subdirectory(Lexer)

add_executable(MoonCompiler src/main.cpp)

target_link_libraries(MoonCompiler PRIVATE Lexer)