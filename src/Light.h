//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H


#include "Vector.h"

class Light {
public:
    Position origin;
};

class PointLight : public Light{
public:

    ///\brief Regle la lumiere
    ///\param position de l'origine de la lumiere
    ///\param angle de la lumiere
    ///\param intensite de la lumiere
    PointLight(const Vector3f& p, const Vector3f& c, const float& i);
    Vector3f col;
    float intensity;
};





#endif //RAYTRACING_LIGHT_H
