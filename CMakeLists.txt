# cmake_minimum_required(VERSION <specify CMake version here>)
project(ShiritoriGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "-fexec-charset=CP949")
add_executable(ShiritoriGame shiritori.cpp shiritori.h main.cpp)