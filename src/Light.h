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

///\brief Classe de la lumiere
class PointLight : public Light{
public:

    ///\brief Regle la lumiere
    ///\param p : position de l'origine de la lumiere
    ///\param c : angle de la lumiere
    ///\param i : intensite de la lumiere
    PointLight(const Vector3f& p, const Vector3f& c, const float& i);
    Vector3f col;
    float intensity;
};





#endif //RAYTRACING_LIGHT_H
