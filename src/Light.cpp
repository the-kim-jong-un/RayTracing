//
// Created by constantin on 11/09/2020.
//

#include "Light.h"

PointLight::PointLight(const Vector3f &p, const Vector3f &c, const float &i) {
    origin=p;
    col=c;
    intensity=i;
}
