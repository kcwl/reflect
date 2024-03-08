project(unittest)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(${GTEST_DIR})

add_executable(unittest test.cpp)

target_link_directories(unittest PUBLIC ${GTEST_LIB})

target_link_libraries(unittest libgtest.a libgtest_main.a)

add_test(NAME unittest COMMAND unittest)