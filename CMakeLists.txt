cmake_minimum_required(VERSION 3.17)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp signal_catcher.cpp signal_catcher.h signal_generator.cpp signal_generator.h reporter.cpp reporter.h)