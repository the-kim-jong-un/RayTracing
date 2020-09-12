#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <utility>
#include <memory>
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
    Renderer * ren;
    Camera::fov=53;
    ren = new Renderer(1000,1000, Vector3f(0));
    Camera::cameraToWorld = Matrix4x4(0.945519, 0, -0.325569, 0, -0.179534, 0.834209, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);
    unsigned int sizeX=1000;
    unsigned int sizeY=1000;

    uint32_t numSpheres = 32;
    gen.seed(time(NULL));
    for (uint32_t i = 0; i < numSpheres; ++i) {
        Vector3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
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

    Sphere * testSp;
    testSp=new Sphere();
    SceneManager::objects.push_back(testSp);
    ren->render();
    return 0;
}
