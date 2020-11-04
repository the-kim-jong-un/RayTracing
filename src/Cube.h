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
    ///\param _corner : Arrete du cube
    Cube(const Vector3f &_corner);

    ~Cube() override;

    ///\brief Affichage de la taille de l'arrete dans la console
    void print() const override;

    ///\brief Calcule la distance entre la surface du cube et l'origine de la lumiere
    ///\param from :
    float getDistance(const Vector3f & from) const override;
    bool intersect(const Ray& ray, float&t) override;

    ///\brief Calcule les normales du cube
    ///\param Phit : Point touché par le rayon
    ///\param Nhit : Normale du point est touché
    ///\param tex : texture du point touché
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override ;

};

#endif //RAYTRACING_CUBE_H
