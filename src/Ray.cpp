//
// Created by constantin on 11/09/2020.
//

#include "Ray.h"
#include "SceneManager.h"

Ray::Ray() {
    this->direction = Vector3f(1);
}

Ray::Ray(const Vector3f &position, const Vector3f &direction) {
    this->position=position;
    this->direction=direction;
}

Vector3f castRay(const Ray& ray){
    Vector3f hitColor = Vector3f() ;
    return hitColor;
}

bool traceRay(const Ray &ray, float &inter, Object *& hitObj) {
    inter = INFINITY;
    unsigned int IndexMax =SceneManager::objects.size();
    for (unsigned int Index=0; Index < IndexMax; Index++){
        float t = INFINITY;
    }
    return false;
}
