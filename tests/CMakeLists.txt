# Explicitly list test files (don't use GLOB - CMake won't reconfigure when new tests are added)
set(TEST_FILES
  test_geometry.cpp
  test_geojson_parser.cpp
  test_linearring.cpp
  test_linestring.cpp
  test_measurements.cpp
  test_multilinestring.cpp
  test_multipoint.cpp
  test_multipolygon.cpp
  test_operations.cpp
  test_point.cpp
  test_polygon.cpp
  test_polyline.cpp
  test_predicates.cpp
  test_transformations.cpp
  test_utils.cpp
)

foreach(file ${TEST_FILES})
  get_filename_component(test_name ${file} NAME_WE)
  message(STATUS "Building target ${test_name}")
  add_executable(${test_name} ${file})
  target_link_libraries(${test_name} ${SHAPES_LIBRARY})
  target_compile_definitions(${test_name} PRIVATE CATCH_CONFIG_MAIN CATCH_CONFIG_NO_POSIX_SIGNALS)
  target_include_directories(${test_name} PUBLIC ${SHAPES_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty)
  add_test(NAME ${test_name} COMMAND ${test_name})

  if(SHAPES_ENABLE_COVERAGE)
    set_target_properties(${test_name} PROPERTIES CXX_STANDARD 14 COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage --coverage")
    target_link_options(${test_name} PUBLIC "--coverage")
  endif()

endforeach()


