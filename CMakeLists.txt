cmake_minimum_required(VERSION 3.7.2)
project(shapes)

set(CMAKE_CXX_STANDARD 14)

# versioning
set(SHAPES_VERSION_MAJOR 0)
set(SHAPES_VERSION_MINOR 1)
set(SHAPES_VERSION_PATCH 0)

find_program(CLANG_FORMAT clang-format)
if(NOT ${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
    file(GLOB_RECURSE HPP_FILES ${PROJECT_SOURCE_DIR}/include/simo/*.hpp)
    add_custom_target(shapes_format COMMENT "applying clang-format"
            COMMAND ${CLANG_FORMAT} -i ${HPP_FILES})
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

add_executable(main main.cpp)
add_executable(test_point tests/test_point.cpp)
add_executable(test_multipoint tests/test_multipoint.cpp)
add_executable(tests_envelope tests/test_envelope.cpp)

