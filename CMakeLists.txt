cmake_minimum_required(VERSION 3.10)
project(Lexer)
set(CMAKE_CXX_STANDARD 14)
find_package(FLEX REQUIRED)

find_package(BISON REQUIRED )
FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
bison_target(bisonParser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS -v)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        LexerExample
        main.cp
        MiniJava.Lexer.h
        ${FLEX_MyScanner_OUTPUTS}
)

