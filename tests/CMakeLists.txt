
file(GLOB files "test_*.cpp")
foreach(file ${files})
    get_filename_component(target_name ${file} NAME_WE)
    message(STATUS "Building target ${target_name}")
    add_executable(${target_name} ${file})
    target_link_libraries(${target_name} ${SHAPES_LIBRARY})
    target_include_directories(${target_name} PUBLIC ${SHAPES_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty)
endforeach()
