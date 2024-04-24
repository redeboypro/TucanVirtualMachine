cmake_minimum_required(VERSION 3.21)
project(TucanVirtualMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(TucanVirtualMachine main.cpp TucanProgram.cpp TucanProgram.h)
