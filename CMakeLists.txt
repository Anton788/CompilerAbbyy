cmake_minimum_required(VERSION 3.10)
project(Lexer)
set(CMAKE_CXX_STANDARD 14)
find_package(FLEX REQUIRED)
FLEX_TARGET(MyScanner lexer.l  ${Lexer_SOURCE_DIR}/MiniJava.lexer.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        LexerExample
        main.cpp
        ${FLEX_MyScanner_OUTPUTS}
)

