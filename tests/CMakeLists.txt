if(SHAPES_ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage -Wno-unused-command-line-argument")

    # collect all source files that we are interested in
    file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/include/simo/*)

    # define target to run lcov to collect coverage information, filter unwanted files, and create HTML report
    add_custom_target(shapes_coverage_report
            COMMAND lcov --directory . --capture --output-file coverage.info --rc lcov_branch_coverage=1
            COMMAND lcov -e coverage.info ${SOURCE_FILES} --output-file coverage.info.filtered --rc lcov_branch_coverage=1
            COMMAND genhtml --title "Shapes ${PROJECT_VERSION}" --legend --demangle-cpp --output-directory coverage_report --show-details --branch-coverage coverage.info.filtered
            COMMENT "Generating HTML report coverage_report/index.html")
endif()


file(GLOB files "test_*.cpp")
foreach(file ${files})
    get_filename_component(test_name ${file} NAME_WE)
    message(STATUS "Building target ${test_name}")
    add_executable(${test_name} ${file})
    target_link_libraries(${test_name} ${SHAPES_LIBRARY})
    target_compile_definitions(${test_name} PRIVATE CATCH_CONFIG_MAIN)
    target_include_directories(${test_name} PUBLIC ${SHAPES_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty)

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()