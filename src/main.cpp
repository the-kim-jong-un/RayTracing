#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <random>
#include <utility>
#include <memory>
#include <chrono>
#include <QApplication>
#include <ctime>
#include "immintrin.h"

#include "Vector.h"
#include "Camera.h"
#include "Ray.h"
#include "SceneManager.h"
#include "Sphere.h"
#include "Renderer.h"
#include "Matrix4x4.h"
#include "Plane.h"
#include "Cube.h"
#include "mainwindow.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

std::vector<Object*> SceneManager::objects;
std::vector<PointLight*> SceneManager::lights;
Matrix4x4 Camera::cameraToWorld;
float Camera::fov;

Renderer::RenderMode Renderer::renderMode;
Renderer::TraceMode Renderer::traceMode;
Vector3f Renderer::backgroundColor;
float Renderer::far=kInfinity;
float Renderer::near=0;

int main(int argc, char *argv[]) {

    //std::chrono::steady_clock sc;
    auto start = std::chrono::steady_clock::now();

    Renderer * ren;
    Camera::fov=53;
    ren = new Renderer(1024,1024, Vector3f(10), Renderer::MULTI,Renderer::SPHERETRACING);
    float spawnSpread = 10;
    int numSpheres = 16;
    gen.seed(time(NULL));
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vector3f randPos((0.5 - dis(gen)) * spawnSpread, (0.5 - dis(gen)) * spawnSpread, (0.5-dis(gen)) * spawnSpread);
        float randRadius =  0.5f + (float)dis(gen) * 0.5f;
        Material tmpMat(Vector3f(dis(gen)/5,dis(gen)/5,dis(gen)/5));
        SceneManager::objects.push_back(new Sphere(randPos, randRadius, tmpMat));
    }





    auto * orig = new Cube(Vector3f(1,1,2));
    orig->mat= Material(Vector3f(0.1,0.1,0.5),0.4,0.02);
    orig->mat.matReflection=1.0f;
    SceneManager::objects.push_back(orig);
    auto * pl = new Plane(Vector3f(0, 1, 0), Vector3f(0, -2, 0));
    SceneManager::objects.push_back(pl);
    auto * testLight = new PointLight(Vector3f (-15,10,15.6),Vector3f(15, 10, 10),500);
    auto * testLight2 = new PointLight(Vector3f (-15,10,12.6),Vector3f(1, 10, 15),200);
    SceneManager::lights.push_back(testLight);
    SceneManager::lights.push_back(testLight2);


    unsigned int fps = 60;
    int frames=1;
    std::cout<< "render mode : " << Renderer::renderMode << '\n';



    double rawDelay = 1 / (double)60;
    double delay=0;
    double deltaTime=0;
    Vector3f lookAtVec = Vector3f(-20, 10, 10);

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
    QApplication a(argc,argv);
    MainWindow mainWindow;
    mainWindow.show();
    a.exec();


    SceneManager::clear();

    delete ren;
    auto end = std::chrono::steady_clock::now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Rendered " <<frames<< " frames in : "<<time_span.count()<<" seconds";
    return 0;
}
