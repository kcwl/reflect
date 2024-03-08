project(unittest)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(${GTEST_DIR})

set(INCLUDES
	generate.h
	no_pod.h
)

set(SOURCES
	test.cpp
)

add_executable(unittest ${INCLUDES} ${SOURCES})

message("gtest lib" ${GTEST_LIB})

target_link_directories(unittest PUBLIC ${GTEST_LIB})

if(WIN32)
set(LIBS libgtest.lib libgtest_main.lib)
else
set(LIBS libgtest.a libgtest_main.a)
endif()

target_link_libraries(unittest ${LIBS})

add_test(NAME unittest COMMAND unittest)