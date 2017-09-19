

file(GLOB SOURCES "*.cpp")
add_library(con_lib STATIC Connection.cpp)

add_executable(hello ${SOURCES})

target_link_libraries(hello con_lib)
