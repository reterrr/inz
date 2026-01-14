cmake_minimum_required(VERSION 3.30)
project(kl_linealg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED)

# Ensure -fPIC is used where needed (works for static libs too)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(runtime STATIC ../runtime.cpp)
target_include_directories(runtime PUBLIC ..)

add_library(linealg SHARED kl_linealg.cpp)
target_include_directories(linealg PRIVATE ..)
target_link_libraries(linealg PRIVATE runtime Eigen3::Eigen)
