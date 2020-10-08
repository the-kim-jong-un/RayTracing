//
// Created by constantin on 01/10/2020.
//

#include "Material.h"

Material::Material(const Vector3f &al, const float &mDif, const float &mSpec, const float &mRef, const float &n) {
    albedo=al;
    matDiffuse=mDif;
    matSpecular=mSpec;
    matReflection=mRef;
    this->n=n;
}
