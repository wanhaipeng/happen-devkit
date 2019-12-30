cmake_minimum_required(VERSION 3.0)
project(yjh_yolov3_deploy_client)

# Assign env variables
set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Ofast -w")

# set include dir
include_directories(${CMAKE_SOURCE_DIR}/include)

# set source file
file(GLOB SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)

# generate exe
add_executable(test_socket_client ${SRCS})

# install exe
install(TARGETS test_socket_client DESTINATION ${CMAKE_SOURCE_DIR}/install)
