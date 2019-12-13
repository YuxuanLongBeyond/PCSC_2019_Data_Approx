cmake_minimum_required(VERSION 3.15)
project(core)

set(CMAKE_CXX_STANDARD 14)

add_executable(core main.cpp src/Matrix.h src/Matrix.cpp src/Fitter.cpp src/Fitter.h test/DataIO.cpp test/DataIO.h plot/gnuplot_i.cpp plot/gnuplot_i.hpp config/Config.cpp config/Config.h test/Experiment_Test.cpp test/Experiment_Test.h)