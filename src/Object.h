//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "Vector.h"
#include "Ray.h"

class Ray;

class Object {
public:
    Position position;

    Object();
    virtual bool intersect(const Ray & ray) = 0;
    virtual ~Object() = 0;

};


#endif //RAYTRACING_OBJECT_H
