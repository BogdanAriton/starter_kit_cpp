cmake_minimum_required(VERSION 3.20)

add_executable(test_proj test_main.cpp)

target_link_libraries(test_proj PUBLIC 
    gtest_main
    gtest
    ${PROJECT_NAME}
)

add_test(
    NAME test_proj
    COMMAND test_proj
)