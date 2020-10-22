//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "Object.h"

class Sphere : public Object{
public:
    float radius;

    ///\brief Constructeur par défaut de Sphere
    Sphere();

    ///\brief Constructeur par copie de Sphere
    ///\param position de la sphere
    ///\param rayon de la sphere
    ///\param matériau de la sphere
    Sphere(const Vector3f& pos, const float & radius,const Material &material);

    ///\brief Destructeur de Sphere
    ~Sphere() override;

    ///\brief Affiche le rayon de la Sphere
    void print() const override;

    ///\brief retourne l'écart entre la surface de la sphere et l'origine de la lumiere
    float getDistance(const Vector3f & from) const override;

    ///\brief
    bool intersect(const Ray& ray, float&t) override;

    ///\brief Calcule la normale de la sphere
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override ;
};


#endif //RAYTRACING_SPHERE_H
