cmake_minimum_required(VERSION 3.20)
project(rv64sim CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Manually add the include path to ELFIO
include_directories(${CMAKE_SOURCE_DIR}/extern/ELFIO)

add_executable(rv64sim src/main.cpp)

