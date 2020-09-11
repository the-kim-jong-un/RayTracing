//
// Created by constantin on 11/09/2020.
//

#include "Ray.h"

Ray::Ray() {
    this->direction = Vector3f(1);
}

Ray::Ray(const Vector3f &position, const Vector3f &direction) {
    this->position=position;
    this->direction=direction;
}
