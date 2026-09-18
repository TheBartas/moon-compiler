cmake_minimum_required(VERSION 3.20)

project(MoonCompiler LANGUAGES CXX)

add_subdirectory(lexer)

add_executable(MoonCompiler src/main.cpp)