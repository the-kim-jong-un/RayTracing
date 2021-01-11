//
// Created by constantin on 28/11/2020.
//

#ifndef RAYTRACING_COMPLEXOBJECTSUBSTRACT_H
#define RAYTRACING_COMPLEXOBJECTSUBSTRACT_H
#include "ComplexObject.h"

///\brief Classe permettant de creer la différence de 2 objets primitifs
class ComplexObjectSubstract : public ComplexObject{
public:
    ///\brief Constructeur de ComplexObjectSubstract
    ///\param _o1 : 1er objet primitif
    ///\param _o2 : 2eme objet primitif
    ComplexObjectSubstract(Object * _o1, Object * _o2);

    ///\brief Destructeur de ComplexObjectSubstract
    ~ComplexObjectSubstract();
    float getDistance(const Vector3f &from) const override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override;
    bool intersect(const Ray &ray, float &t) override;
    void print() const override;
};


#endif //RAYTRACING_COMPLEXOBJECTSUBSTRACT_H
