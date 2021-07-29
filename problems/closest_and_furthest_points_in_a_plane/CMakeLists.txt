cmake_minimum_required(VERSION 3.20)

# setting a variable pointing at project
set(PROJECT_NAME myProject)
project(${PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

enable_testing()
add_subdirectory(googletest)

# put all headers here
set (Headers
closest_points.hpp
)

# put all sources here
set (Sources
closest_points.cpp
)

# creating main as an executable and the rest of the code as static library linked to main and linked with the test
add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})
add_executable(main main.cpp)

target_link_libraries(main ${PROJECT_NAME})

add_subdirectory(tests)
