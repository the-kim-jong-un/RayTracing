//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "Vector.h"
#include "Ray.h"
#include "Material.h"
const float kInfinity = std::numeric_limits<float>::max();
class Ray;

class Object {
public:
    Position position;
    Vector3f color;
    Material mat;
    Object();
    virtual void print() const  =0;
    virtual bool intersect(const Ray & ray, float & t) = 0;
    virtual float getDistance(const Vector3f & from) const =0;
    virtual void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const =0 ;
    virtual ~Object() = 0;

    [[maybe_unused]] void debug() const;
};


#endif //RAYTRACING_OBJECT_H
