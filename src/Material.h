//
// Created by constantin on 01/10/2020.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H


#include "Vector.h"

class Material {
public:
    ///\brief Gère les types de lumières (speculaire/réflexive/diffuse)
    ///\param al :
    ///\param mDiff : lumiere diffuse
    ///\param mRef : lumiere réflexive
    ///\param n : lumiere spéculaire
    Material(const Vector3f & al= Vector3f(0.18,0.18,0.18) ,const float & mDif=0.8, const float & mSpec=0.08, const float &mRef=1.f, const float & n=4);
    Vector3f albedo;
    float matDiffuse;
    float matReflection;
    float matSpecular, n;
};


#endif //RAYTRACING_MATERIAL_H
