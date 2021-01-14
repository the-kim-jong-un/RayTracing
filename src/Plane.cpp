//
// Created by constantin on 24/09/2020.
//

#include "Plane.h"

float Plane::getDistance(const Vector3f &from) const {
    return (n.dotProduct(from - pointOnPlane));
}

Plane::Plane(const Vector3f &nn, const Vector3f &pp) {
    n=nn;
    pointOnPlane=pp;
}

void Plane::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const {

}

bool Plane::intersect(const Ray &ray, float &t) {
    return false;
}

void Plane::print() const {

}

Plane::~Plane() = default;