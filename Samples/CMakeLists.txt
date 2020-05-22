cmake_minimum_required(VERSION 3.10)

set(samples_dir ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

file(GLOB samples ${samples_dir}/*.java)
foreach(file ${samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
            NAME Test${filename}.java
            COMMAND ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )

    add_test(
            NAME MemoryTest${filename}.java
            COMMAND valgrind ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )

endforeach()

