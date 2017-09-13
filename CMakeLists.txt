cmake_minimum_required(VERSION 2.8.9)

project(hello)

set(CURRENT_INCLUDE include)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/libs)

link_directories(${CMAKE_HOME_DIRECTORY}/libs)
include_directories(${CURRENT_INCLUDE})
add_subdirectory (src)

enable_testing()
add_subdirectory (tests)

