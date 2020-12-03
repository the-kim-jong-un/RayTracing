//
// Created by constantin on 29/11/2020.
//

#include "ComplexObjectIntersect.h"

ComplexObjectIntersect::ComplexObjectIntersect(Object *_o1, Object *_o2) : ComplexObject(_o1, _o2) {

}

ComplexObjectIntersect::~ComplexObjectIntersect() {

}

float ComplexObjectIntersect::getDistance(const Vector3f &from) const {
    return std::max(o1->getDistance(from),o2->getDistance(from));
}

void ComplexObjectIntersect::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const {

}

bool ComplexObjectIntersect::intersect(const Ray &ray, float &t) {
    return false;
}

void ComplexObjectIntersect::print() const {

}
