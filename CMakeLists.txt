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

# Trie library
add_library(Trie STATIC)
target_sources(Trie PRIVATE
        src/trie.cc)
target_include_directories(Trie PRIVATE
        src)
target_compile_options(Trie PRIVATE
        -Wall -Wextra -pedantic)

# Static lib
add_library(Lib STATIC)
target_sources(Lib PRIVATE
        lib/contract.cc
        lib/indent.cc
        lib/indent.hh)
target_include_directories(Lib PRIVATE
        lib)
target_compile_options(Trie PRIVATE
        -Wall -Wextra -pedantic)



# First executable
add_executable(TextMiningCompiler)
target_sources(TextMiningCompiler PRIVATE
        src/compiler/main.cc
        src/compiler/parser.cc)
target_include_directories(TextMiningCompiler PRIVATE
        src
        src/compiler)
target_link_libraries(TextMiningCompiler PRIVATE
        Trie
        Lib)
target_compile_options(TextMiningCompiler PRIVATE
        -Wall -Wextra -pedantic)


# Second executable
add_executable(TextMiningApp)
target_sources(TextMiningApp PRIVATE
        src/app/main.cc)
target_include_directories(TextMiningApp PRIVATE
        src)
target_link_libraries(TextMiningApp PRIVATE
        Trie)
target_compile_options(TextMiningApp PRIVATE
        -Wall -Wextra -pedantic)
