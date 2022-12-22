cmake_minimum_required(VERSION 3.2)
project(gbx_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(gbx_test main.cpp database.cpp)


enable_testing()


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_database test_database.cpp database.cpp)
target_link_libraries(test_database ${GTEST_LIBRARIES} pthread)

add_test(NAME TestDatabase COMMAND test_database)
