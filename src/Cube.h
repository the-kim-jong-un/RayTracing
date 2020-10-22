//
// Created by alban on 08/10/2020.
//

#ifndef RAYTRACING_CUBE_H
#define RAYTRACING_CUBE_H

#include "Object.h"

class Cube : public Object{
public:

    Vector3f corner{0.25, 0.25, 0.25};

    ///\brief Constructeur par défaut de Cube
    Cube();

    ///\brief Constructeur par copie de Cube
    ///\param
    Cube(const Vector3f &_corner);
    ~Cube() override;
    void print() const override;
    float getDistance(const Vector3f & from) const override;
    bool intersect(const Ray& ray, float&t) override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override ;

};

#endif //RAYTRACING_CUBE_H
