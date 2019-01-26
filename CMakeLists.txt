cmake_minimum_required(VERSION 3.7.2)

project(shapes LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE on)

# versioning
set(SHAPES_VERSION_MAJOR 0)
set(SHAPES_VERSION_MINOR 1)
set(SHAPES_VERSION_PATCH 0)

# format
find_program(CLANG_FORMAT clang-format)
if (NOT ${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
    file(GLOB_RECURSE HPP_FILES
            ${PROJECT_SOURCE_DIR}/include/simo/*.hpp
            ${PROJECT_SOURCE_DIR}/include/simo/io/*.hpp
            ${PROJECT_SOURCE_DIR}/include/simo/geom/*.hpp)
    add_custom_target(shapes_format COMMENT "applying clang-format"
            COMMAND ${CLANG_FORMAT} -i ${HPP_FILES})
endif ()


add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} INTERFACE)

target_include_directories(
        ${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/single_include/>
        $<INSTALL_INTERFACE:include>
)

# @todo first find python
add_custom_target(amalgamate COMMENT "merging the headers"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND python ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/amalgamate.py -c ${PROJECT_SOURCE_DIR}/thirdparty/amalgamate/config.json -s . --verbose=yes)


add_subdirectory(tests)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/single_include/"
    DESTINATION "include"
)

export(
    TARGETS ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake"
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    INCLUDES DESTINATION "include"
)

install(
    EXPORT "${PROJECT_NAME}Targets"
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "lib/cmake/${PROJECT_NAME}"
)
