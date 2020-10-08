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
    Sphere(const Vector3f& pos, const float & radius,const Material &material);
    ~Sphere() override;
    void print() const override;
    float getDistance(const Vector3f & from) const override;
    bool intersect(const Ray& ray, float&t) override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override ;
};


#endif //RAYTRACING_SPHERE_H
