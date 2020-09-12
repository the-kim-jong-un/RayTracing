#include <iostream>
#include <cmath>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "SceneManager.h"
#include "Sphere.h"

std::vector<Object*> SceneManager::objects;
std::vector<Light*> SceneManager::lights;

int main() {
    unsigned int sizeX=1000;
    unsigned int sizeY=1000;
    Vector3f test(1,2,3);
    Vector3f add(5,0,2);
    Object *Base;
    Base = new Sphere;
    SceneManager::objects.push_back(Base);
    test = normalize(test) + add;
    test.print();
    float T = INFINITY;
    return 0;
}
