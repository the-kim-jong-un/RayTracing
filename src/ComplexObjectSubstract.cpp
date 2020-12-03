//
// Created by constantin on 28/11/2020.
//

#include "ComplexObjectSubstract.h"
#include <cmath>


ComplexObjectSubstract::ComplexObjectSubstract(Object *_o1, Object *_o2) : ComplexObject(_o1, _o2) {

}



float ComplexObjectSubstract::getDistance(const Vector3f &from) const {
    return std::max(o1->getDistance(from),-o2->getDistance(from));
}

void ComplexObjectSubstract::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const {

}

bool ComplexObjectSubstract::intersect(const Ray &ray, float &t) {
    return false;
}

void ComplexObjectSubstract::print() const {

}
