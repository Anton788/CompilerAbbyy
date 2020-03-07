cmake_minimum_required(VERSION 3.12)
project(Abbyy)
set(CMAKE_CXX_STANDARD 14)
find_package(FLEX)
FLEX_TARGET(MyScanner lexer.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(
        MyCompiler
        main.cpp
        ${FLEX_MyScanner_OUTPUTS}
        )

