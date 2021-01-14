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
#include "Renderer.h"
#include "Matrix4x4.h"
#include "mainwindow.h"


std::vector<Object *> SceneManager::objects;
std::vector<PointLight *> SceneManager::lights;
Matrix4x4 Camera::cameraToWorld;
float Camera::fov;

SceneManager *SceneManager::self;
bool SceneManager::bIsLoading = false;
Renderer *Renderer::self;
unsigned int Renderer::sampleAccuracy = 0;
Renderer::RenderMode Renderer::renderMode;
Renderer::TraceMode Renderer::traceMode;
Vector3f Renderer::backgroundColor;
float Renderer::far = kInfinity;
float Renderer::near = 0;
bool Renderer::running = false;
MainWindow *Renderer::mw;
QByteArray *Renderer::Qarr;
unsigned int Renderer::width;
unsigned int Renderer::height;

void LaunchWindow(int argc, char **argv) {
    QApplication a(argc, argv);
    Renderer::mw = new MainWindow;
    Renderer::mw->show();
    a.exec();
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::steady_clock::now();
    Renderer *ren;
    SceneManager sc;
    std::thread win(&LaunchWindow, argc, argv);
    Camera::fov = 53;
    ren = new Renderer(1024, 1024, Vector3f(10), Renderer::MULTI, Renderer::SPHERETRACING);
    win.join();

    SceneManager::clear();

    delete ren;
    return 0;
}
