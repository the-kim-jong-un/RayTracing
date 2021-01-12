//
// Created by constantin on 28/11/2020.
//

#ifndef RAYTRACING_COMPLEXOBJECT_H
#define RAYTRACING_COMPLEXOBJECT_H
#include "Object.h"

///\brief Super-classe abstraite d'objets complexes
class ComplexObject : public Object {
public:
    Object * o1;
    Object * o2;

    ///\brief Constructeur de ComplexObject
    ///\param _o1 : 1er objet primitif
    ///\param _o2 : 2eme objet primitif
    ComplexObject(Object * _o1, Object * _o2);

    ///\brief Destructeur de ComplexObject
    ~ComplexObject();


    virtual float getDistance(const Vector3f &from) const=0;
    virtual bool intersect(const Ray &ray, float &t)=0;
    virtual void getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const=0;
    virtual void print() const=0;


};


#endif //RAYTRACING_COMPLEXOBJECT_H
