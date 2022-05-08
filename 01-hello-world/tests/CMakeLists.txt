cmake_minimum_required(VERSION 3.10.2)

project(tests)

enable_testing()

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
gtest
boost_filesystem
)
