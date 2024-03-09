cmake_minimum_required(VERSION 3.2)

if(WIN32)
cmake_policy(SET CMP0091 NEW)
option(MSVC_STATIC_RUNTIME "build static runtime" ON)

if(MSVC_STATIC_RUNTIME)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()
endif()

enable_language(CXX)

project(reflect)

set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd/googletest/googletest/include)

set(GTEST_LIB ${CMAKE_CURRENT_SOURCE_DIR}/build/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(cmake/CodeCoverage.cmake)
APPEND_COVERAGE_COMPILER_FLAGS()

enable_testing()

add_subdirectory(3rd/googletest)

add_subdirectory(unittest)