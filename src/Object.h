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

    ///\brief Constructeur de Object
    Object();

    ///\brief Affichage console
    virtual void print() const  =0;
    virtual bool intersect(const Ray & ray, float & t) = 0;

    ///\brief Calcule l'écart entre l'origine de la lumiere et la surface de l'objet
    virtual float getDistance(const Vector3f & from) const =0;

    ///\brief Calcule la normale
    virtual void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const =0 ;

    ///\brief Destructeur de Object
    virtual ~Object() = 0;

    [[maybe_unused]] void debug() const;
};


#endif //RAYTRACING_OBJECT_H
