cmake_minimum_required(VERSION 3.10)


set(CMAKE_C_COMPILER gcc)

set(CMAKE_CXX_COMPILER g++)


project(task2_3)# ^ Name of project

message(INFO:\ "Write image")
# ^ Log message
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${task2_3_SOURCE_DIR}/bin)
# ^ Directory where store build of project
include_directories(include/)
# include_directories(-I/path/to/iostream/directory)
# ^ Directory with headers to be included (like -I option of compiler)

add_executable(task2_3  main.cpp src/utils.cpp) 
# ^ Create executable with sources