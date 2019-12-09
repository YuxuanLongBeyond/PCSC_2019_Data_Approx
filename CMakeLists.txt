cmake_minimum_required(VERSION 3.15)
project(project)

set(CMAKE_CXX_STANDARD 14)

add_executable(project main.cpp src/Matrix.h src/Matrix.cpp src/Fitter.cpp src/Fitter.h test/DataIO.cpp test/DataIO.h test/gnuplot_i.cpp test/gnuplot_i.hpp config/Config.cpp config/Config.h test/Test.cpp test/Test.h)