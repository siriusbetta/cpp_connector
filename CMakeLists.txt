cmake_minimum_required(VERSION 2.8.9)

project(server)

set(CURRENT_INCLUDE include)
add_compile_options(-std=c++11)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/temp_libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

link_directories(${CMAKE_HOME_DIRECTORY}/libs)
include_directories(${CURRENT_INCLUDE})
add_subdirectory (src)

enable_testing()
add_subdirectory (tests)

