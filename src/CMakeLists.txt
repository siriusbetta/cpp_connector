

file(GLOB SOURCES "*.cpp")
add_library(fac_lib SHARED factorial.cpp)

add_executable(hello ${SOURCES})

target_link_libraries(hello fac_lib)
