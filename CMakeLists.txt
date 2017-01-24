set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required (VERSION 2.8.2)
project (watermark CXX C)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
ADD_DEFINITIONS(-std=c++1z)
include_directories(${CMAKE_SOURCE_DIR}/src)
find_package(OpenCV REQUIRED)

add_executable(decode ${SOURCE_FILES} main/decode.cpp)
add_executable(encode ${SOURCE_FILES} main/encode.cpp)

target_link_libraries(decode ${OpenCV_LIBS})
target_link_libraries(encode ${OpenCV_LIBS})
