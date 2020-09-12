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
    Position position;
    Vector3f direction;
    Ray();
    Ray(const Position & position, const Vector3f & direction);
};

bool traceRay(const Ray &ray, float &inter, Object *& hitObj);
Vector3f castRay(const Ray& ray);

#endif //RAYTRACING_RAY_H
