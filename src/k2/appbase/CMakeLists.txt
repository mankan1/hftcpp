cmake_minimum_required(VERSION 3.18)

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

#project(searstar-learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OK)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Seastar_CXX_DIALECT "gnu++20" CACHE STRING "")

#add_subdirectory(../../seastar)

add_library(k2appbase STATIC ${HEADERS} ${SOURCES})

#set_target_properties(k2appbase PROPERTIES
#VERSION ${PROJECT_VERSION}
#SOVERSION 1
#)

#add_executable(hello-world main.cc)
#target_link_libraries(hello-world Seastar::seastar)

target_link_libraries (k2appbase PRIVATE Seastar::seastar )
