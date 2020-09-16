//
// Created by constantin on 11/09/2020.
//

#include "Ray.h"
#include "SceneManager.h"
#include "Renderer.h"

const float kInfinity = std::numeric_limits<float>::max();

inline
Vector3f mix(const Vector3f &a, const Vector3f & b, const float &mixValue)
{ return a * (1 - mixValue) + b * mixValue; }


Ray::Ray() {
    this->direction = Vector3f(1);
}

Ray::Ray(const Vector3f &position, const Vector3f &direction) {
    this->position=position;
    this->direction=direction;
}

Vector3f castRay(const Ray& ray){
    Vector3f hitColor;
    Object *hitObject = nullptr; // this is a pointer to the hit object
    float t; // this is the intersection distance from the ray origin to the hit point
    if (traceRay(ray, t, hitObject)) {
        Vector3f Phit = ray.position + ray.direction * t;
        Vector3f Nhit;
        Vector3f tex;
        hitObject->getSurfaceData(Phit, Nhit, tex);
        // Use the normal and texture coordinates to shade the hit point.
        // The normal is used to compute a simple facing ratio and the texture coordinate
        // to compute a basic checker board pattern
        float scale = 4;
        float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
        hitColor = std::max(0.f, Nhit.dotProduct(-1.0f*ray.direction)) * mix(hitObject->color, hitObject->color * 0.8f, pattern);
        //hitColor.print();
    } else {
        hitColor= Renderer::backgroundColor;
        //hitColor.print();
    }
    return hitColor;
}

bool traceRay(const Ray &ray, float &inter, Object *& hitObj) {
    inter = kInfinity;
    unsigned int IndexMax =SceneManager::objects.size();
    for (unsigned int Index=0; Index < IndexMax; Index++){
        float t = kInfinity;
        bool res = SceneManager::objects[Index]->intersect(ray,t);
        if (res && t<inter){
            //ray.origin.print();
            //ray.direction.print();
            hitObj=SceneManager::objects[Index];
            inter = t;
        }
    }
    //std::cout<<inter<<'\n';
    return (hitObj != nullptr);
}
