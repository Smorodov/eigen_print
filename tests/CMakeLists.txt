if(BUILD_TESTS)
enable_testing()
find_package(Catch2 QUIET)
if(NOT Catch2_FOUND)
include(FetchContent)
FetchContent_Declare(
Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG v3.8.0
)
FetchContent_MakeAvailable(Catch2)
endif()
set(TEST_SOURCES
test_matrix.cpp
test_sparse.cpp
test_options.cpp
test_print.cpp
test_tensor.cpp
)
add_executable(test_eigen_print ${TEST_SOURCES})
target_link_libraries(test_eigen_print PRIVATE
EigenPrint::eigen_print
Catch2::Catch2WithMain
)
target_include_directories(test_eigen_print PRIVATE
 
{CMAKE_CURRENT_SOURCE_DIR}/..
${EIGEN_INCLUDE_DIRS}
)
target_compile_features(test_eigen_print PRIVATE cxx_std_20)
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
target_compile_options(test_eigen_print PRIVATE -O3 -march=native -mtune=native)
endif()
add_test(NAME test_eigen_print COMMAND test_eigen_print)
endif()