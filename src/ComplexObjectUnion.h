//
// Created by constantin on 28/11/2020.
//

#ifndef RAYTRACING_COMPLEXOBJECTUNION_H
#define RAYTRACING_COMPLEXOBJECTUNION_H
#include "ComplexObject.h"

class ComplexObjectUnion : public ComplexObject {
public:

    ComplexObjectUnion(Object * _o1, Object * _o2);
    ~ComplexObjectUnion() override;
    float getDistance(const Vector3f &from) const override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override;
    bool intersect(const Ray &ray, float &t) override;
    void print() const override;

};


#endif //RAYTRACING_COMPLEXOBJECTUNION_H
