cmake_minimum_required(VERSION 3.10)
project(asoa_linux_examples)

set(CMAKE_BUILD_TYPE Release)

find_package(fastrtps 2.3.2 REQUIRED)
find_package(fastcdr REQUIRED)

add_executable(hello_world "main.cpp")
target_link_libraries(hello_world fastcdr fastrtps)
