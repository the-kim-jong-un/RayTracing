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
#include "ComplexObjectUnion.h"
#include "ComplexObjectSubstract.h"
#include "ComplexObjectIntersect.h"
#include "mainwindow.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

std::vector<Object*> SceneManager::objects;
std::vector<PointLight*> SceneManager::lights;
Matrix4x4 Camera::cameraToWorld;
float Camera::fov;

SceneManager * SceneManager::self;
Renderer * Renderer::self;
unsigned int Renderer::sampleAcuracy=0;
Renderer::RenderMode Renderer::renderMode;
Renderer::TraceMode Renderer::traceMode;
Vector3f Renderer::backgroundColor;
float Renderer::far=kInfinity;
float Renderer::near=0;
bool Renderer::running=false;
MainWindow * Renderer::mw;
QByteArray * Renderer::Qarr;
unsigned int Renderer::width;
unsigned int Renderer::height;

void testlaunchWindow(int argc, char *argv[]){
    QApplication a(argc,argv);
    //MainWindow mainWindow;
    Renderer::mw = new MainWindow;
    //mainWindow.show();
    Renderer::mw->show();
    a.exec();
}



int main(int argc, char *argv[]) {
    auto start = std::chrono::steady_clock::now();

    Renderer * ren;
    SceneManager sc;
    std::thread win(&testlaunchWindow,argc,argv);

    //std::this_thread::sleep_for(std::chrono::milliseconds((int) 1000));

    Camera::fov=53;
    ren = new Renderer(1024,1024, Vector3f(10), Renderer::MULTI,Renderer::SPHERETRACING);
    float spawnSpread = 12;
    int numSpheres = 0;
    gen.seed(time(NULL));
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vector3f randPos((0.5 - dis(gen)) * spawnSpread, (0.5 - dis(gen)) * spawnSpread, (0.5-dis(gen)) * spawnSpread);
        float randRadius =  0.5f + (float)dis(gen) * 0.5f;
        Material tmpMat(Vector3f(dis(gen)/5,dis(gen)/5,dis(gen)/5));
        SceneManager::objects.push_back(new Sphere(randPos, randRadius, tmpMat));
    }






    auto * testLight2 = new PointLight(Vector3f (5,10,-5),Vector3f(1, 10, 15),400);
    //SceneManager::addLight(testLight2);


    unsigned int fps = 60;
    int frames=1;
    std::cout<< "render mode : " << Renderer::renderMode << '\n';



    double rawDelay = 1 / (double)60;
    double delay=0;
    double deltaTime=0;
    Vector3f lookAtVec = Vector3f(-20, 10, 10);
    //Vector3f lookAtVec = Vector3f(-10, 9, 10) * 1.0f;
    //Vector3f lookAtVec = Vector3f(-15, 40, 0);

    for (int i=0;i<frames;i++){
        auto fpsStart = std::chrono::high_resolution_clock::now();
        //lookAtVec=lookAtVec.rotateAround('y', 0.02f);
        std::cout<<"frame : "<<i<<'\n';
        Camera::cameraToWorld=Camera::lookAt(lookAtVec, Vector3f());

        //ren->render();

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

    auto end = std::chrono::steady_clock::now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Rendered " <<frames<< " frames in : "<<time_span.count()<<" seconds"<<'\n';

    win.join();
    //QApplication a(argc,argv);
    //MainWindow mainWindow;
    //mainWindow.show();
    //a.exec();


    SceneManager::clear();

    delete ren;
    return 0;
}
