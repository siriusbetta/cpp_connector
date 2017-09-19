

file(GLOB SOURCES "*.cpp")
#add_library(fac_lib STATIC factorial.cpp)

add_executable(hello ${SOURCES})

#target_link_libraries(hello fac_lib)
