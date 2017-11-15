cmake_minimum_required(VERSION 3.7)
project(nettools)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_subdirectory(nettools)
add_subdirectory(tests)
add_subdirectory(jni)

target_include_directories(jni-nettools PRIVATE $ENV{JDK}include)
