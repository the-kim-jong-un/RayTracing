//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "Vector.h"

class Object {
public:
    Position position;

    Object();
    virtual bool intersect();
    virtual ~Object();

};


#endif //RAYTRACING_OBJECT_H