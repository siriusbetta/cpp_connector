
set(CATCH_INCLUDE ${CURRENT_INCLUDE}/catch)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE})

add_executable(test_hello test.cpp)
target_link_libraries(test_hello Catch fac_test)

