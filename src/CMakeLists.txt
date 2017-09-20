

file(GLOB SOURCES "*.cpp")
#add_library(con_lib STATIC Connection.cpp)
add_library(con_lib STATIC ${SOURCES})

#add_executable(hello ${SOURCES})
add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(server con_lib)
target_link_libraries(client con_lib)
