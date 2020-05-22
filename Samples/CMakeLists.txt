cmake_minimum_required(VERSION 3.10)

set(samples_dir ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

file(GLOB good_samples ${samples_dir}/good_samples/*.java)
foreach(file ${good_samples})
    get_filename_component(filename ${file} NAME_WE)
    add_test(
            NAME GoodTest${filename}.java
            COMMAND ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/good_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
    add_test(
            NAME GoodMemoryTest${filename}.java
            COMMAND valgrind ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/good_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
endforeach()

file(GLOB bad_samples ${samples_dir}/bad_samples/*.java)
foreach(file ${bad_samples})
    get_filename_component(filename ${file} NAME_WE)

    add_test(
            NAME BadTest${filename}.java
            COMMAND ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/bad_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )

    add_test(
            NAME BadMemoryTest${filename}.java
            COMMAND valgrind ${CMAKE_BINARY_DIR}/Lexer lexer ${CMAKE_SOURCE_DIR}/Samples/bad_samples/${filename}.java
            WORKING_DIRECTORY ${samples_dir}
    )
endforeach()
