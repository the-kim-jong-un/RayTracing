//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Vector.h"
#include "Object.h"
class Object;

class Ray {
public:
    Position origin;
    Vector3f direction;
    Ray();
    Ray(const Position & position, const Vector3f & direction);
};

Vector3f sphereTrace(const Ray &ray);
Vector3f stepColoring(const unsigned int& steps);
bool traceRay(const Ray &ray, float &inter, Object *& hitObj);
Vector3f castRay(const Ray& ray);
Vector3f shade(const Ray &ray, const float &t, Object * interObject);
bool sphereTraceShadow(const Ray &ray,const float &maxDist);


#endif //RAYTRACING_RAY_H
