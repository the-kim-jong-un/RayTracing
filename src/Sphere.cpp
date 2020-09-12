//
// Created by constantin on 11/09/2020.
//

#include "Sphere.h"

bool Sphere::intersect(const Ray & ray) {
    return false;
}

Sphere::~Sphere(){

}

Sphere::Sphere() {
    position=Vector3f();
    radius=1;
}
