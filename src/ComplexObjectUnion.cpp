//
// Created by constantin on 28/11/2020.
//

#include "ComplexObjectUnion.h"

float ComplexObjectUnion::getDistance(const Vector3f &from) const {
    return std::min(o1->getDistance(from),o2->getDistance(from));
}

ComplexObjectUnion::~ComplexObjectUnion() {

}

ComplexObjectUnion::ComplexObjectUnion(Object *_o1, Object *_o2) : ComplexObject(_o1, _o2) {

}

void ComplexObjectUnion::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const {

}

bool ComplexObjectUnion::intersect(const Ray &ray, float &t) {
    return false;
}

void ComplexObjectUnion::print() const {

}
