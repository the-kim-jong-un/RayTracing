#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <random>
#include <utility>
#include <memory>
#include <chrono>
#include <ctime>
#include "immintrin.h"

#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include "SceneManager.h"
#include "Sphere.h"
#include "Renderer.h"
#include "Matrix4x4.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

std::vector<Object*> SceneManager::objects;
std::vector<Light*> SceneManager::lights;
Matrix4x4 Camera::cameraToWorld;
float Camera::fov;

Vector3f Renderer::backgroundColor;

int main() {

    std::chrono::steady_clock sc;
    auto start = sc.now();

    Renderer * ren;
    Camera::fov=55;
    ren = new Renderer(512,512, Vector3f(0));
    //Camera::cameraToWorld = Matrix4x4(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);
    //Camera::cameraToWorld=Camera::lookAt(Vector3f(40,0,0),Vector3f());
    unsigned int sizeX=1000;
    unsigned int sizeY=1000;

    int numSpheres = 64;
    gen.seed(time(NULL));
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vector3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5-dis(gen)) * 10);
        float randRadius = (0.5 + dis(gen) * 0.5);
        int randcolor = dis(gen)*6;
        Vector3f Color;
        if(randcolor==0)
            Color = Vector3f(255);
        else if(randcolor ==1)
            Color = Vector3f(255,255);
        else if(randcolor ==2)
            Color = Vector3f(0,255,255);
        else if(randcolor ==3)
            Color = Vector3f(255,0,255);
        else if(randcolor ==4)
            Color = Vector3f(0,255);
        else
            Color = Vector3f(0,0,255);
        SceneManager::objects.push_back(new Sphere(randPos, randRadius, Color));
    }
    Sphere * orig = new Sphere(Vector3f(),1,Vector3f(255));
    SceneManager::objects.push_back(orig);

    int fps = 60;
    int frames=64;
    double rawDelay = 1 / (double)60;
    double delay=0;
    double deltaTime=0;
    Vector3f lookatVec = Vector3f(-20,0,0);
    //std::cout<<"ref mag : "<<lookatVec.mag()<<'\n';

    for (int i=0;i<frames;i++){
        auto fpsStart = std::chrono::high_resolution_clock::now();
        lookatVec=lookatVec.rotateAround('y', .2f*deltaTime,Vector3f());
        std::cout<<"frame : "<<i<<'\n';
        Camera::cameraToWorld=Camera::lookAt(lookatVec,Vector3f());
        ren->renderThread();
        auto fpsEnd = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(fpsEnd - fpsStart);
        //std::cout << elapsed.count() << "/" << rawDelay << '\n';
        if (elapsed.count() < rawDelay || false){
            delay= rawDelay - elapsed.count();
            std::cout << "delay : " << delay << '\n';
            deltaTime=delay + elapsed.count()/10;
            std::cout << "total : " << deltaTime << '\n' << '\n';

            std::this_thread::sleep_for(std::chrono::milliseconds((int) delay));
        } else deltaTime=elapsed.count()/1;
    }


    for (int index=0; index<SceneManager::objects.size(); index++){
        delete SceneManager::objects[index];
    }
    SceneManager::objects.empty();
    delete ren;
    auto end = sc.now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Rendered " <<frames<< " frames in : "<<time_span.count()<<" seconds";
    return 0;
}
