//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "Object.h"

class Sphere : public Object{
public:
    float radius;

    Sphere();
    ~Sphere() override;
    bool intersect(const Ray& ray) override;

};


#endif //RAYTRACING_SPHERE_H
