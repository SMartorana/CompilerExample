cmake_minimum_required(VERSION 3.14.0)

set(PROJ_NAME "Compiler_Example")
project(${PROJ_NAME} VERSION 0.0.0 LANGUAGES CXX)

add_library(ce INTERFACE)
target_include_directories(ce INTERFACE include)

target_compile_features(ce INTERFACE cxx_std_20)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(examples)