cmake_minimum_required(VERSION 3.15)
project(untitled C)

LINK_LIBRARIES("OpenCL")
set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c opencl_utility.c opencl_utility.h error.c error.h interface.c interface.h)