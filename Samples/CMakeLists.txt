cmake_minimum_required(VERSION 3.10)

set(good_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/good_samples)
set(bad_samples_dir ${CMAKE_CURRENT_SOURCE_DIR}/bad_samples)

enable_testing()

file(GLOB good_samples ${good_samples_dir}/*.java)
file(GLOB bad_samples ${bad_samples_dir}/*.java)

foreach(file ${good_samples})
    get_filename_component(filename ${file} NAME_WE)
    add_test(
            NAME GoodTest${filename}.java
            COMMAND ${CMAKE_BINARY_DIR}/Lexer check ${CMAKE_SOURCE_DIR}/Samples/good_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
    add_test(
            NAME GoodMemoryTest${filename}.java
            COMMAND valgrind ${CMAKE_BINARY_DIR}/Lexer check ${CMAKE_SOURCE_DIR}/Samples/good_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
endforeach()

foreach(file ${bad_samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
            NAME BadTest${filename}.java
            COMMAND ${CMAKE_BINARY_DIR}/Lexer check ${CMAKE_SOURCE_DIR}/Samples/bad_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
    add_test(
            NAME BadMemoryTest${filename}.java
            COMMAND valgrind ${CMAKE_BINARY_DIR}/Lexer check ${CMAKE_SOURCE_DIR}/Samples/bad_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
endforeach()