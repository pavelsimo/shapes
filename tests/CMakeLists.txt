if(SHAPES_ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "--coverage -g -O0 -fprofile-arcs -ftest-coverage -Wno-unused-command-line-argument")
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