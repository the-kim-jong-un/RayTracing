//
// Created by constantin on 11/09/2020.
//

#include "Ray.h"
#include "SceneManager.h"
#include "Renderer.h"


inline
Vector3f mix(const Vector3f &a, const Vector3f & b, const float &mixValue)
{ return a * (1 - mixValue) + b * mixValue; }


Ray::Ray() {
    this->direction = Vector3f(1);
}

Ray::Ray(const Vector3f &position, const Vector3f &direction) {
    this->origin=position;
    this->direction=direction;
}

Vector3f castRay(const Ray& ray){
    Vector3f hitColor;
    Object *hitObject = nullptr; // this is a pointer to the hit object
    float t; // this is the intersection distance from the ray origin to the hit point
    if (traceRay(ray, t, hitObject)) {
        Vector3f Phit = ray.origin + ray.direction * t;
        Vector3f Nhit;
        Vector3f tex;
        hitObject->getSurfaceData(Phit, Nhit, tex);
        // Use the normal and texture coordinates to shade the hit point.
        // The normal is used to compute a simple facing ratio and the texture coordinate
        // to compute a basic checker board pattern
        float scale = 4;
        float pattern = (fmodf(tex.x * scale, 1) > 0.5f) ^ (fmodf(tex.y * scale, 1) > 0.5);
        hitColor = std::max(0.f, Nhit.dotProduct(-1.0f*ray.direction)) * mix(hitObject->color, hitObject->color * 0.8f, pattern);
        //hitColor.print();
    } else {
        hitColor= Renderer::backgroundColor;
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
            hitObj=SceneManager::objects[Index];
            inter = t;
        }
    }
    return (hitObj != nullptr);
}

Vector3f sphereTrace(const Ray &ray) {
    const float maxDist=150.0f;
    const double limit=55e-6;
    float t=0;
    unsigned int steps=0;
    Object *interObject = nullptr;

    while (t<maxDist) {
        float minDist = kInfinity;
        Vector3f from = ray.origin + t* ray.direction;
        for(auto objects : SceneManager::objects){
            float dist = objects->getDistance(from);
            if (dist<minDist){
                minDist=dist;
                interObject=objects;
            }
        }

        if (minDist<= limit*t){
            //return stepColoring(steps);
            /*
            Vector3f Phit = ray.origin + ray.direction * t;
            Vector3f Nhit;
            Vector3f tex;
            interObject->getSurfaceData(Phit, Nhit, tex);
            // Use the normal and texture coordinates to shade the hit point.
            // The normal is used to compute a simple facing ratio and the texture coordinate
            // to compute a basic checker board pattern
            float scale = 4;
            float pattern = (fmodf(tex.x * scale, 1) > 0.5f) ^ (fmodf(tex.y * scale, 1) > 0.5);
            return std::max(0.f, Nhit.dotProduct(-1.0f*ray.direction)) * mix(interObject->color, interObject->color * 0.8f, pattern);
            //hitColor.print();*/
            return shade(ray,t,interObject);
        }

        t+=minDist;
        ++steps;
    }
    return Vector3f();
}

Vector3f stepColoring(const unsigned int &steps) {

    float greyscale=255 - clamp(0,255,steps*4);
    //std::cout<<steps<<"//"<<greyscale<<'\n';
    return Vector3f(greyscale,greyscale,greyscale);
}

Vector3f shade(const Ray &ray, const float &t, Object * interObject) {
    const float delta= 10e-6;
    Vector3f p= ray.origin+t*ray.direction; ;
    Vector3f norm=Vector3f (
            interObject->getDistance(p+Vector3f(delta)) - interObject->getDistance(p+Vector3f(-delta)),
            interObject->getDistance(p+Vector3f(0,delta)) - interObject->getDistance(p+Vector3f(0,-delta)),
            interObject->getDistance(p+Vector3f(0,0,delta)) - interObject->getDistance(p+Vector3f(0,0,-delta))
            );
    norm=normalize(norm);
    Vector3f R= Vector3f();

    for(auto light : SceneManager::lights){
        Vector3f lightDir=light->origin - p;
        if (lightDir.dotProduct(norm)>0){
            float dist2= lightDir.norm(); //TODO
            lightDir= normalize(lightDir);
            bool shadow = 1 - sphereTraceShadow(Ray(p,lightDir), sqrtf(dist2));
            Vector3f clampedCol =(float)shadow * lightDir.dotProduct(norm) * light->col * light->intensity / (float)(4 * M_PI * dist2);
            clampedCol = Vector3f(clamp(0,255,clampedCol.x),clamp(0,255,clampedCol.y),clamp(0,255,clampedCol.z));
            R = R + (clampedCol);
        }
    }




    return R;
}

bool sphereTraceShadow(const Ray &ray,const float &maxDist) {
    const float limit = 10e-5;
    float t=0;

    while (t<maxDist){
        float minDist =kInfinity;
        Vector3f from =ray.origin + t* ray.direction;
        for(auto objects : SceneManager::objects){
            float dist = objects->getDistance(from);
            if (dist <minDist){
                minDist=dist;
                if (minDist<=limit*t){
                    return true;
                }
            }
        }
        t+=minDist;
    }
    return false;
}

inline
float clamp(const float & low, const float & high, const float &val){
    return std::max(low, std::min(high,val));
}
