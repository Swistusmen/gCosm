cmake_minimum_required(VERSION "3.1.0")
project(gCosmTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(gCosmTest 
    main_test.cpp
    Parser/parser_test.cpp
)

target_link_libraries(gCosmTest ${GTEST_LIBRARIES} pthread)