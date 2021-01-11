//
// Created by constantin on 29/11/2020.
//

#ifndef RAYTRACING_COMPLEXOBJECTINTERSECT_H
#define RAYTRACING_COMPLEXOBJECTINTERSECT_H
#include "ComplexObject.h"

///\brief Classe permettant de creer l'intersection de 2 objets primitifs
class ComplexObjectIntersect: public ComplexObject {
public:
    ///\brief Constructeur de ComplexObjectIntersect
    ///\param _o1 : 1er objet primitif
    ///\param _o2 : 2eme objet primitif
    ComplexObjectIntersect(Object * _o1, Object * _o2);

    ///\brief Destructeur de ComplexObjectIntersect
    ~ComplexObjectIntersect() override;
    float getDistance(const Vector3f &from) const override;
    void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const override;
    bool intersect(const Ray &ray, float &t) override;
    void print() const override;

};


#endif //RAYTRACING_COMPLEXOBJECTINTERSECT_H
