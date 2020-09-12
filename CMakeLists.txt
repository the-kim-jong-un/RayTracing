cmake_minimum_required(VERSION 3.16)
project(Raytracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(Raytracing src/main.cpp src/Object.cpp src/Object.h src/Sphere.cpp src/Sphere.h src/Vector.cpp src/Vector.h src/Ray.cpp src/Ray.h src/SceneManager.cpp src/SceneManager.h src/Light.cpp src/Light.h src/Renderer.cpp src/Renderer.h src/Matrix4x4.cpp src/Matrix4x4.h src/Camera.cpp src/Camera.h)