if(BUILD_EXAMPLES)
    function(add_example NAME SOURCE)
        add_executable(${NAME} ${SOURCE})
        target_link_libraries(${NAME} PRIVATE EigenPrint::eigen_print)
        target_include_directories(${NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../include
            ${CMAKE_CURRENT_SOURCE_DIR}/..
            ${EIGEN_INCLUDE_DIRS}
        )
        target_compile_features(${NAME} PRIVATE cxx_std_20)
        if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_compile_options(${NAME} PRIVATE -O3 -march=native -mtune=native)
        endif()
    endfunction()
    add_example(example_matrix example_matrix.cpp)
    add_example(example_sparse example_sparse.cpp)
    add_example(example_tensor example_tensor.cpp)
endif()