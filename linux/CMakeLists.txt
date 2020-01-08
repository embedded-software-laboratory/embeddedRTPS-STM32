cmake_minimum_required(VERSION 3.13)
project(embedded_test)
set (CMAKE_CXX_STANDARD 11)

include_directories(include)

add_subdirectory(thirdparty/x86_64)

add_executable(main "main.cpp")
target_link_libraries(main asoa_rtps_driver)

