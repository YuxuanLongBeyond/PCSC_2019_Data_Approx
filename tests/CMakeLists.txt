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
        ../core/experiment/DataIO.h
        ../core/experiment/DataIO.cpp
        ../core/experiment/Experiment_Test.h
        ../core/experiment/Experiment_Test.cpp)

target_link_libraries(int_test gtest gtest_main)