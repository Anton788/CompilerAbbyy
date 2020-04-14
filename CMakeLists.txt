cmake_minimum_required(VERSION 3.10)
project(Lexer)
set(CMAKE_CXX_STANDARD 14)
find_package(FLEX )

find_package(BISON  )

FLEX_TARGET( MyLexer ${CMAKE_SOURCE_DIR}/sources/lexer.l
        ${CMAKE_BINARY_DIR}/kLexer.cpp
        COMPILE_FLAGS --header=${CMAKE_BINARY_DIR}/kLexer.h )

BISON_TARGET( MyParser ${CMAKE_SOURCE_DIR}/sources/parser.y
        ${CMAKE_BINARY_DIR}/kParser.cpp
        VERBOSE
        )

add_executable(
        Lexer
        ${CMAKE_SOURCE_DIR}/sources/main.cpp
        ${CMAKE_SOURCE_DIR}/sources/CompVisitor.cpp
        ${FLEX_MyLexer_OUTPUTS}
        ${BISON_MyParser_OUTPUTS}
)
target_include_directories( Lexer PRIVATE ${CMAKE_BINARY_DIR} )
target_include_directories( Lexer PRIVATE ${CMAKE_SOURCE_DIR}/sources )