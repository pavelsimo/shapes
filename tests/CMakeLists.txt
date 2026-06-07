# Explicitly list test files (don't use GLOB - CMake won't reconfigure when new tests are added)
add_library(shapes_catch2 STATIC ${PROJECT_SOURCE_DIR}/thirdparty/catch2/catch_amalgamated.cpp)
target_compile_features(shapes_catch2 PUBLIC cxx_std_14)
target_compile_definitions(shapes_catch2 PUBLIC CATCH_CONFIG_NO_POSIX_SIGNALS)
target_include_directories(shapes_catch2 SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/thirdparty)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
  target_compile_options(shapes_catch2 PRIVATE -w)
elseif(MSVC)
  target_compile_options(shapes_catch2 PRIVATE /w)
endif()

set(TEST_FILES
  test_geometry.cpp
  test_geojson_parser.cpp
  test_io.cpp
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
  test_wkb.cpp
)

foreach(file ${TEST_FILES})
  get_filename_component(test_name ${file} NAME_WE)
  message(STATUS "Building target ${test_name}")
  add_executable(${test_name} ${file})
  target_link_libraries(${test_name} PRIVATE ${SHAPES_LIBRARY} shapes_catch2)
  add_test(NAME ${test_name} COMMAND ${test_name})

  if(SHAPES_ENABLE_COVERAGE)
    set_target_properties(${test_name} PROPERTIES CXX_STANDARD 14 COMPILE_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage --coverage")
    target_link_options(${test_name} PUBLIC "--coverage")
  endif()

endforeach()
