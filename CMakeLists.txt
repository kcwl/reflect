cmake_minimum_required(VERSION 3.2)

project(reflect)

set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/googletest/googletest/include)

set(GTEST_LIB ${CMAKE_CURRENT_SOURCE_DIR}/3rd/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_subdirectory(3rd/googletest)

add_subdirectory(unittest)