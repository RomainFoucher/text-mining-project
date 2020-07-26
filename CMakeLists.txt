cmake_minimum_required(VERSION 3.14)
project(TextMining)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

message("set to ${CMAKE_BUILD_TYPE} mode")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native -fipa-pta -ftree-loop-linear -floop-strip-mine -floop-block -ftree-loop-if-convert -ftree-parallelize-loops=8")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-inline -fno-builtin")

# Common library
add_library(Common STATIC)
target_sources(Common PRIVATE
        src/bst.cc)
target_include_directories(Common PRIVATE
        src)
target_compile_options(Common PRIVATE
        -Wall -Wextra -pedantic)


# First executable
add_executable(TextMiningCompiler)
target_sources(TextMiningCompiler PRIVATE
        src/compiler/main.cc
        src/compiler/parser.cc
        src/compiler/patricia.cc
        src/compiler/trie.cc)
target_include_directories(TextMiningCompiler PRIVATE
        src
        src/compiler)
target_link_libraries(TextMiningCompiler PRIVATE
        Common)
target_compile_options(TextMiningCompiler PRIVATE
        -Wall -Wextra -pedantic)


# Second executable
add_executable(TextMiningApp)
target_sources(TextMiningApp PRIVATE
        src/app/main.cc
        src/app/patricia.cc
        src/app/search.cc)
target_include_directories(TextMiningApp PRIVATE
        src
        src/app)
target_link_libraries(TextMiningApp PRIVATE
        Common)
target_compile_options(TextMiningApp PRIVATE
        -Wall -Wextra -pedantic)
