cmake_minimum_required(VERSION 3.15)
project(untitled C)

LINK_LIBRARIES("OpenCL")
set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c gpu_task.c gpu_task.h file/file.c file/file.h)