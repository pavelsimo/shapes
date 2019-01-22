
add_executable(test_point test_point.cpp)
target_link_libraries(test_point shapes)
target_include_directories(test_point PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdparty)



