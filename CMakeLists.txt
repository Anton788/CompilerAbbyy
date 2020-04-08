cmake_minimum_required(VERSION 3.12)
project(Abbyy)
set(CMAKE_CXX_STANDARD 14)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED )
FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
bison_target(bisonParser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS -v)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(
        MyCompiler
        main.cpp
        MiniJava.Lexer.h
        ${FLEX_MyScanner_OUTPUTS}
        #${BISON_bisonParser_OUTPUTS}
        )

