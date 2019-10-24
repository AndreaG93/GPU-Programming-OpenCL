cmake_minimum_required(VERSION 3.15)
project(untitled C)

LINK_LIBRARIES("OpenCL")
set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c opencl_utility.c opencl_utility.h error/error.c error/error.h interface.c interface.h file/file.c file/file.h)