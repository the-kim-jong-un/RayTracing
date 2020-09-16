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

Renderer::RenderMode Renderer::renderMode;
Vector3f Renderer::backgroundColor;

int main() {

    //std::chrono::steady_clock sc;
    auto start = std::chrono::steady_clock::now();

    Renderer * ren;
    Camera::fov=55;
    ren = new Renderer(2048,2048, Vector3f(0), Renderer::MULTI);
    float spawnSpread = 40;



    int numSpheres = 1024;
    gen.seed(time(NULL));
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vector3f randPos((0.5 - dis(gen)) * spawnSpread, (0.5 - dis(gen)) * spawnSpread, (0.5-dis(gen)) * spawnSpread);
        float randRadius =  0.5f + (float)dis(gen) * 0.5f;
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

    Sphere * orig = new Sphere(Vector3f(),1,Vector3f(255,255,255));
    SceneManager::objects.push_back(orig);


    unsigned int fps = 60;
    int frames=1;
    std::cout<< "render mode : " << Renderer::renderMode << '\n';


    double rawDelay = 1 / (double)60;
    double delay=0;
    double deltaTime=0;
    Vector3f lookAtVec = Vector3f(-60, 10, 0);

    for (int i=0;i<frames;i++){
        auto fpsStart = std::chrono::high_resolution_clock::now();
        lookAtVec=lookAtVec.rotateAround('y', 0.02f);
        std::cout<<"frame : "<<i<<'\n';
        Camera::cameraToWorld=Camera::lookAt(lookAtVec, Vector3f());

        ren->render();

        auto fpsEnd = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(fpsEnd - fpsStart);
        //std::cout << elapsed.count() << "/" << rawDelay << '\n';
        if (elapsed.count() < rawDelay){
            delay= rawDelay - elapsed.count();
            std::cout << "delay : " << delay << '\n';
            deltaTime=delay + elapsed.count()/10;
            std::cout << "total : " << deltaTime << '\n' << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds((int) delay));
        } else deltaTime=elapsed.count()/1;
    }

    SceneManager::clear();

    delete ren;
    auto end = std::chrono::steady_clock::now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Rendered " <<frames<< " frames in : "<<time_span.count()<<" seconds";
    return 0;
}
