cmake_minimum_required(VERSION 3.20)
project(book-analyzer)

find_package(Boost REQUIRED COMPONENTS program_options)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${Boost_INCLUDE_DIRS})
add_executable(book-analyzer book-analyzer.cpp)
target_link_libraries(book-analyzer ${Boost_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(book-analyzer-tests book-analyzer-tests.cpp )
target_link_libraries(book-analyzer-tests ${GTEST_BOTH_LIBRARIES})