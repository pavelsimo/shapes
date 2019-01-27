# https://github.com/nlohmann/json/blob/develop/test/CMakeLists.txt#L28
if(SHAPES_COVERAGE)

    message(STATUS "Building test suite with coverage information")
    if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(FATAL_ERROR "JSON_Coverage requires GCC.")
    endif()

    # enable profiling
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage")

    # from https://github.com/RWTH-HPC/CMake-codecov/blob/master/cmake/FindGcov.cmake
    get_filename_component(COMPILER_PATH "${CMAKE_CXX_COMPILER}" PATH)
    string(REGEX MATCH "^[0-9]+" GCC_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
    find_program(GCOV_BIN NAMES gcov-${GCC_VERSION} gcov HINTS ${COMPILER_PATH})

    # collect all source files from the chosen include dir
    file(GLOB_RECURSE SOURCE_FILES ${SHAPES_INCLUDE_DIR}*.hpp)

    # add target to collect coverage information and generate HTML file
    # (filter script from https://stackoverflow.com/a/43726240/266378)
    add_custom_target(lcov_html
            COMMAND lcov --directory . --capture --output-file shapes.info --gcov-tool ${GCOV_BIN} --rc lcov_branch_coverage=1
            COMMAND lcov -e shapes.info ${SOURCE_FILES} --output-file shapes.info.filtered --rc lcov_branch_coverage=1
            COMMAND ${CMAKE_SOURCE_DIR}/test/thirdparty/imapdl/filterbr.py shapes.info.filtered > shapes.info.filtered.noexcept
            COMMAND genhtml --title "shapes" --legend --demangle-cpp --output-directory html --show-details --branch-coverage shapes.info.filtered.noexcept
            COMMENT "Generating HTML report tests/html/index.html"
            )
endif()

file(GLOB files "test_*.cpp")
foreach(file ${files})
    get_filename_component(target_name ${file} NAME_WE)
    message(STATUS "Building target ${target_name}")
    add_executable(${target_name} ${file})
    target_link_libraries(${target_name} ${SHAPES_LIBRARY})
    target_include_directories(${target_name} PUBLIC ${SHAPES_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty)
endforeach()
