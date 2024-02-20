cmake_minimum_required(VERSION 3.27)
project(lee)

set(CMAKE_CXX_STANDARD 17)

add_library(lee_impl Map.cpp)

add_executable(lee main.cpp black_box/IO.cpp)
target_link_libraries(lee lee_impl)

add_subdirectory(test)
