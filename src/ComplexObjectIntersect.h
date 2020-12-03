//
// Created by constantin on 29/11/2020.
//

#ifndef RAYTRACING_COMPLEXOBJECTINTERSECT_H
#define RAYTRACING_COMPLEXOBJECTINTERSECT_H
#include "ComplexObject.h"

class ComplexObjectIntersect: public ComplexObject {
public:
    ComplexObjectIntersect(Object * _o1, Object * _o2);
    ~ComplexObjectIntersect() override;
    float getDistance(const Vector3f &from) const override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override;
    bool intersect(const Ray &ray, float &t) override;
    void print() const override;

};


#endif //RAYTRACING_COMPLEXOBJECTINTERSECT_H
