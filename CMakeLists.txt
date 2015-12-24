cmake_minimum_required(VERSION 2.8)
project(cluster)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp utils/utils.cpp utils/utils.h matrix/Matrix.cpp matrix/Matrix.h cluster.cpp cluster.h data/data.cpp data/data.h)

add_executable(cluster ${SOURCE_FILES})