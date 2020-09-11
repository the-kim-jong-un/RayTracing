cmake_minimum_required(VERSION 3.16)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracing src/main.cpp src/Object.cpp src/Object.h src/Sphere.cpp src/Sphere.h src/Vector.cpp src/Vector.h)