cmake_minimum_required(VERSION 3.7.2)

project(shapes LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE on)

# versioning
set(SHAPES_VERSION_MAJOR 0)
set(SHAPES_VERSION_MINOR 1)
set(SHAPES_VERSION_PATCH 0)

set(SHAPES_LIBRARY ${PROJECT_NAME})

# warning settings
if (MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# include settings
option(SHAPES_SINGLE_HEADER "whether to use a single header or multiple headers" ON)
if (SHAPES_SINGLE_HEADER)
    set(SHAPES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/single_include)
else()
    set(SHAPES_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
endif()

# clang-format
find_program(CLANG_FORMAT clang-format)
if (NOT ${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
    file(GLOB_RECURSE HPP_FILES
            ${PROJECT_SOURCE_DIR}/include/simo/*.hpp
            ${PROJECT_SOURCE_DIR}/include/simo/io/*.hpp
            ${PROJECT_SOURCE_DIR}/include/simo/geom/*.hpp
            ${PROJECT_SOURCE_DIR}/tests/*.cpp
            )
    add_custom_target(shapes_format COMMENT "applying clang-format"
            COMMAND ${CLANG_FORMAT} -i ${HPP_FILES})
endif ()

add_library(${SHAPES_LIBRARY} INTERFACE)
add_library(${SHAPES_LIBRARY}::${SHAPES_LIBRARY} ALIAS ${SHAPES_LIBRARY})
target_compile_features(${SHAPES_LIBRARY} INTERFACE)
if (SHAPES_SINGLE_HEADER)
    add_dependencies(${SHAPES_LIBRARY} amalgamate)
endif()

target_include_directories(
        ${SHAPES_LIBRARY}
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/single_include/>
        $<INSTALL_INTERFACE:include>
)

# amalgamate
add_custom_target(amalgamate COMMENT "merging the headers"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND python ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/amalgamate.py -c ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/config.json -s . --verbose=yes)

add_subdirectory(tests)
