cmake_minimum_required(VERSION 2.8)

project(ram)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -g")

add_subdirectory(src)

add_executable(ram src/ParserException.cpp src/Program.cpp src/main.cpp)

install(TARGETS ram RUNTIME DESTINATION bin)
