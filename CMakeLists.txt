cmake_minimum_required(VERSION 3.7.2)
project(shapes)

set(CMAKE_CXX_STANDARD 14)

# versioning
set(SHAPES_VERSION_MAJOR 0)
set(SHAPES_VERSION_MINOR 1)
set(SHAPES_VERSION_PATCH 0)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(main main.cpp)

