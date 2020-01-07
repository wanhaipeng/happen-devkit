cmake_minimum_required(VERSION 3.5)
project(multi_thread)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Ofast")

# found opencv
find_package(OpenCV REQUIRED)

# set include dir
set(MULTI_THREAD_INCLUDE ${CMAKE_SOURCE_DIR}/include)
include_directories(${MULTI_THREAD_INCLUDE}
                    ${OpenCV_INCLUDE_DIRS})

# set libraries dir
# message(STATUS ${OpenCV_LIBRARIES})
link_libraries(${OpenCV_LIBRARIES}
               pthread)

# set source file
aux_source_directory(${CMAKE_SOURCE_DIR}/src MULTI_THREAD_SRCS)

# generate executable

add_executable(multi_thread ${MULTI_THREAD_SRCS})

# install executable
install(TARGETS multi_thread RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/install)