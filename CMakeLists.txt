cmake_minimum_required(VERSION 3.12)
project(eigen_print VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -mtune=native -DNDEBUG")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /arch:AVX2")
endif()

find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)

get_target_property(EIGEN_INCLUDE_DIRS Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
if(NOT EIGEN_INCLUDE_DIRS)
    set(EIGEN_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif()

if(EIGEN_INCLUDE_DIRS MATCHES "/eigen3$")
    get_filename_component(EIGEN_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS} DIRECTORY)
endif()

message(STATUS "Eigen include path: ${EIGEN_INCLUDE_DIRS}")
message(STATUS "fmt version: ${fmt_VERSION}")

add_library(eigen_print INTERFACE)
add_library(EigenPrint::eigen_print ALIAS eigen_print)

target_include_directories(eigen_print INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
    ${EIGEN_INCLUDE_DIRS}
)

target_link_libraries(eigen_print INTERFACE
    Eigen3::Eigen
    fmt::fmt
)

add_subdirectory(tests)
add_subdirectory(examples)

message(STATUS "")
message(STATUS "eigen_print Configuration:")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Eigen3: ${EIGEN_INCLUDE_DIRS}")
message(STATUS "  fmt: ${fmt_VERSION}")
message(STATUS "  Tests: ${BUILD_TESTS}")
message(STATUS "  Examples: ${BUILD_EXAMPLES}")
message(STATUS "")