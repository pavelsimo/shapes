
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE on)

add_executable(test_point test_point.cpp)
target_link_libraries(test_point shapes)
target_include_directories(test_point PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdparty)

add_executable(test_multipoint test_multipoint.cpp)
target_link_libraries(test_multipoint shapes)
target_include_directories(test_multipoint PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/thirdparty)



