cmake_minimum_required(VERSION 3.10)


set(CMAKE_C_COMPILER gcc)

set(CMAKE_CXX_COMPILER g++)

project(trig_lib)
# ^ Name of project

message(INFO:\ "trigonometric function library")
# ^ Log message
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${trig_lib_SOURCE_DIR}/bin)
# ^ Directory where store build of project

include_directories(-I/path/to/iostream/directory)
# ^ Directory with headers to be included (like -I option of compiler)

add_executable(trig_lib main.cpp src/my_math.cpp) 
# ^ Create executable with sources