cmake_minimum_required(VERSION 3.14)
project(TextMining)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

message("set to ${CMAKE_BUILD_TYPE} mode")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native -fipa-pta -ftree-loop-linear -floop-strip-mine -floop-block -ftree-loop-if-convert -ftree-parallelize-loops=8")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-inline -fno-builtin -fsanitize=address")

# Common library
add_library(Common STATIC)
target_sources(Common PRIVATE
        src/patricia/patricia.cc)
target_include_directories(Common PRIVATE
        src/patricia)
target_compile_options(Common PRIVATE
        -Wall -Wextra -pedantic)


# First executable
add_executable(TextMiningCompiler)
target_sources(TextMiningCompiler PRIVATE
        src/compiler/main.cc
        src/compiler/parser.cc
        src/compiler/patricia_builder.cc
        src/compiler/trie.cc)
target_include_directories(TextMiningCompiler PRIVATE
        src/compiler
        src)
target_link_libraries(TextMiningCompiler PRIVATE
        Common)
target_compile_options(TextMiningCompiler PRIVATE
        -Wall -Wextra -pedantic)


# Second executable
add_executable(TextMiningApp)
target_sources(TextMiningApp PRIVATE
        src/app/main.cc
        src/app/parser.cc
        src/app/search.cc)
target_include_directories(TextMiningApp PRIVATE
        src/app
        src)
target_link_libraries(TextMiningApp PRIVATE
        Common)
target_compile_options(TextMiningApp PRIVATE
        -Wall -Wextra -pedantic)


# Doxygen
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
