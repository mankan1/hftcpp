cmake_minimum_required(VERSION 3.18)

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

project(searstar-learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OK)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Seastar_CXX_DIALECT "gnu++20" CACHE STRING "")

add_subdirectory(seastar)

add_subdirectory (src)

#add_library(k2appbase STATIC ${HEADERS} ${SOURCES})

#set_target_properties(k2appbase PROPERTIES
#	VERSION ${PROJECT_VERSION}
#	SOVERSION 1
#)

add_executable(hello-world main.cc)
target_link_libraries(hello-world PRIVATE k2appbase Seastar::seastar)

#target_link_libraries (k2appbase PRIVATE Seastar::seastar )

#####
# cmake_minimum_required (VERSION 3.13)

# project (k2_platform VERSION 0.0.1 LANGUAGES CXX)
# set(CMAKE_CXX_STANDARD 17)
# add_compile_options(-O3 -g -Werror -Wall -Wextra -march=skylake -mtune=skylake-avx512 -mavx -mavx2 -mxsave -mbmi -mbmi2 -mlzcnt -maes -mpopcnt)

# # K2_DEBUG_LOGGING enables some verbose logging for debug purposes.
# if(DEFINED ENV{K2_DEBUG_LOGGING})
# 	set(K2_DEBUG_LOGGING $ENV{K2_DEBUG_LOGGING})
# else()
#     set(K2_DEBUG_LOGGING 0)
# endif()

# add_compile_definitions(K2_DEBUG_LOGGING=${K2_DEBUG_LOGGING})

# include_directories(src)

# find_package (Seastar REQUIRED)
# find_package (yaml-cpp REQUIRED) # required for configuration file parsing

# add_subdirectory (src)
# add_subdirectory (test)