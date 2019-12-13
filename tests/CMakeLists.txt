cmake_minimum_required(VERSION 3.15)
project(integration_tests)

#Add the google test subdirectory
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
##include googletest/include dir
#include_directories(/Users/YuxuanLong/Desktop/MATH458/googletest)


set(CMAKE_CXX_STANDARD 14)

file(GLOB project_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ../core/src/*.cpp
        ../core/src/*.h)

add_executable(int_test
        main.cpp
        debug_test.cpp
        ${project_src}
        ../core/test/DataIO.h
        ../core/test/DataIO.cpp
        ../core/test/Experiment_Test.h
        ../core/test/Experiment_Test.cpp)
#add_executable(google_test main.cpp debug_test.cpp ../project/test/DataIO.h ../project/test/DataIO.cpp)

#add_custom_command(TARGET int_test POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/matlab_data
#        ${CMAKE_CURRENT_BINARY_DIR}/matlab_data)

target_link_libraries(int_test gtest gtest_main)