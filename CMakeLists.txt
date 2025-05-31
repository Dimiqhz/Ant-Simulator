cmake_minimum_required(VERSION 3.16)
project(AntSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ant_simulator ${SOURCES})