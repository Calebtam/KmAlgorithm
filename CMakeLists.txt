cmake_minimum_required(VERSION 2.8)
project(test_pro)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(test1 test1.cpp)
target_link_libraries(test1 )

add_executable(test2 test2.cpp)
target_link_libraries(test2 )

add_executable(test3 test3.cpp)
target_link_libraries(test3 )

add_executable(test4 test4.cpp)
target_link_libraries(test4 )