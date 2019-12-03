cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp Matrix.h Matrix.cpp Fitter.cpp Fitter.h Inputdata.cpp Inputdata.h)