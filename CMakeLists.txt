cmake_minimum_required(VERSION 3.1)

project(shapes LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)

# regex
set(HAVE_STD_REGEX 1)
add_definitions(-DHAVE_STD_REGEX)
set(CMAKE_VERBOSE_MAKEFILE on)

# versioning
set(SHAPES_VERSION_MAJOR 0)
set(SHAPES_VERSION_MINOR 0)
set(SHAPES_VERSION_PATCH 1)

set(SHAPES_LIBRARY ${PROJECT_NAME})

####################
# warning settings #
####################
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

####################
# include settings #
####################
option(SHAPES_SINGLE_HEADER "whether to use a single header or multiple headers" OFF)
if (SHAPES_SINGLE_HEADER)
    set(SHAPES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/single_include)
else()
    set(SHAPES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
endif()


add_library(${SHAPES_LIBRARY} INTERFACE)
add_library(${SHAPES_LIBRARY}::${SHAPES_LIBRARY} ALIAS ${SHAPES_LIBRARY})
target_compile_features(${SHAPES_LIBRARY} INTERFACE)
if (SHAPES_SINGLE_HEADER)
    add_dependencies(${SHAPES_LIBRARY} amalgamate)
endif()

target_include_directories(
        ${SHAPES_LIBRARY}
        INTERFACE
        $<BUILD_INTERFACE:${SHAPES_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)

file(GLOB_RECURSE HPP_FILES
    ${PROJECT_SOURCE_DIR}/include/simo/*.hpp
    ${PROJECT_SOURCE_DIR}/include/simo/geom/*.hpp
    #${PROJECT_SOURCE_DIR}/include/simo/io/*.hpp
    ${PROJECT_SOURCE_DIR}/tests/*.cpp
)

################
# clang-format #
################
find_program(CLANG_FORMAT clang-format)
if (NOT ${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
    add_custom_target(shapes_format COMMENT "applying clang-format"
            COMMAND ${CLANG_FORMAT} -i ${HPP_FILES})
else()
    message(STATUS "clang-format not found")
endif ()

##############
# clang-tidy #
##############

add_custom_target(shapes_clang_tidy COMMENT "applying clang-tidy"
        COMMAND clang-tidy -p=${PROJECT_BINARY_DIR} -checks=modernize-*,cppcoreguidelines-*,portability-*,bugprone-*,readability-*,cert-* ${HPP_FILES})

##############
# amalgamate #
##############
add_custom_target(shapes_amalgamate COMMENT "merging the headers"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND python ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/amalgamate.py -c ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/config.json -s . --verbose=yes)

##############
# re2c lexer #
##############
add_custom_target(shapes_lexer COMMENT "re2c lexer code generation"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/include/simo/io
        COMMAND re2c -i -b -o wkt_lexer.hpp wkt_lexer.re)

################
# lemon parser #
################
add_custom_target(shapes_parser COMMENT "lemon parser"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/include/simo/io
        COMMAND lemon -m -q -l wkt_parser.y)

###########
# doxygen #
###########
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found")
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(shapes_documentation
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else()
    message(STATUS "Doxygen not found")
endif()

include(CTest)
option(SHAPES_TESTING "build tests" ON)
if(SHAPES_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
