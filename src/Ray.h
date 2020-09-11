//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Vector.h"

class Ray {
public:
    Position position;
    Vector3f direction;
    Ray();
    Ray(const Position & position, const Vector3f & direction);
};

Vector3f castRay(const Ray& ray);

#endif //RAYTRACING_RAY_H
