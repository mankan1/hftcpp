cmake_minimum_required(VERSION 3.18)
project(searstar-learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OK)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Seastar_CXX_DIALECT "gnu++20" CACHE STRING "")

add_subdirectory(seastar)
add_executable(hello-world main.cc)
target_link_libraries(hello-world Seastar::seastar)
