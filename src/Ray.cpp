//
// Created by constantin on 11/09/2020.
//

#include <random>
#include "Ray.h"
#include "SceneManager.h"
#include "Renderer.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);

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

Vector3f sphereTrace(const Ray &ray,const unsigned int & depth, Vector3f &dBuffer) {
    const float maxDist=128.0f;
    float minDist = kInfinity;
    const double limit=15e-5;
    float t=0;
    float glowDist;
    unsigned int steps=0;
    Object *interObject = nullptr;
    if (depth>Renderer::maxDepth) return Vector3f();
    while (t<maxDist && steps <2048) {
        minDist=kInfinity;
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
            dBuffer=Vector3f(1,1,1)*t;
            return shade(ray,t,interObject,depth);// /(float)((255 - steps)/255);
        }
        t+=minDist;
        ++steps;
    }
    dBuffer=Vector3f(1,1,1)*(maxDist);
    return Renderer::backgroundColor;
}

Vector3f stepColoring(const unsigned int &steps) {

    float greyscale=255 - clamp(0,255,steps*6);
    //std::cout<<steps<<"//"<<greyscale<<'\n';
    return Vector3f(greyscale,greyscale,greyscale);
}

Vector3f shade(const Ray &ray, const float &t, Object * interObject,const unsigned int & depth) {
    const float delta= 10e-6;
    Vector3f p= ray.origin+t*ray.direction; ;
    Vector3f norm=Vector3f (
            interObject->getDistance(p+Vector3f(delta)) - interObject->getDistance(p+Vector3f(-delta)),
            interObject->getDistance(p+Vector3f(0,delta)) - interObject->getDistance(p+Vector3f(0,-delta)),
            interObject->getDistance(p+Vector3f(0,0,delta)) - interObject->getDistance(p+Vector3f(0,0,-delta))
            );
    norm=normalize(norm);
    Vector3f hitCol= Vector3f();
    Vector3f diffuse;
    Vector3f specular=Vector3f();
    Vector3f reflection;
    Vector3f indirectLightningCol;
    for(auto light : SceneManager::lights){
        Vector3f lightDir=light->origin - p;
        if (lightDir.dotProduct(norm)>0){
            float dist2= lightDir.norm(); //TODO
            lightDir= normalize(lightDir);
            bool shadow = 1 - sphereTraceShadow(Ray(p,lightDir), sqrtf(dist2));
            diffuse= diffuse+ (float)shadow * interObject->mat.albedo * light->intensity * std::max(0.f,norm.dotProduct(1.0f*lightDir));
            //diffuse= diffuse+ (float)shadow * interObject->mat.albedo * light->intensity * std::max(0.f,norm.dotProduct(1.0f*lightDir));
            Vector3f R= reflect(lightDir,norm);
            float tmp= (float)shadow* light->intensity * std::pow(std::max(0.f,R.dotProduct(1.f*ray.direction)),interObject->mat.n);
            specular= specular + Vector3f(tmp,tmp,tmp);


            //Vector3f clampedCol =(float)shadow * lightDir.dotProduct(norm) * light->col * light->intensity / (float)(4 * M_PI * dist2);
            //clampedCol = Vector3f(clamp(0,255,clampedCol.x),clamp(0,255,clampedCol.y),clamp(0,255,clampedCol.z));
            //hitCol = hitCol + (clampedCol);

        }

        Vector3f R= reflect(ray.direction,norm);
        Vector3f tbuff;
        reflection= reflection + (sphereTrace(Ray(p,R),depth+1,tbuff));
        Vector3f tmpdiff=Vector3f(diffuse.x, diffuse.y, diffuse.z);
        Vector3f tmpspec=Vector3f(specular.x,specular.y,specular.z);
        reflection = reflection / ((float)Renderer::maxDepth);
        hitCol = tmpdiff * interObject->mat.matDiffuse + tmpspec * interObject->mat.matSpecular + reflection * interObject->mat.matReflection;
        //Vector3f clampedColor = Vector3f(clamp(0,255,hitCol.x),clamp(0,255,hitCol.y),clamp(0,255,hitCol.z));
        //hitCol = reflection * interObject->mat.matReflection;
    }
    if (depth < Renderer::maxSampleDepth){
        Vector3f Nt,Nb;
        createCoordinateSystem(norm,Nt,Nb);
        float pdf = 1 / (1 * M_PI);
        for (int n = 0; n < Renderer::sampleAcuracy; ++n) {
            float r1 = distribution(generator);
            float r2 = distribution(generator);
            Vector3f sample = uniformSampleHemisphere(r1, r2);
            Vector3f sampleWorld(
                    sample.x * Nb.x + sample.y * norm.x + sample.z * Nt.x,
                    sample.x * Nb.y + sample.y * norm.y + sample.z * Nt.y,
                    sample.x * Nb.z + sample.y * norm.z + sample.z * Nt.z);
            // don't forget to divide by PDF and multiply by cos(theta)
            Vector3f tbuff;
            indirectLightningCol = indirectLightningCol + (r1 * sphereTrace(Ray(p+sampleWorld*0.001f,sampleWorld),depth + 1,tbuff)/pdf);
        }
    }
    indirectLightningCol = indirectLightningCol /(float)Renderer::sampleAcuracy;
    if (Renderer::sampleAcuracy>0) {
        hitCol = ((hitCol / (float) 1) + 1.f * Vector3f(indirectLightningCol.x * interObject->mat.albedo.x,
                                                        indirectLightningCol.y * interObject->mat.albedo.y,
                                                        indirectLightningCol.z * interObject->mat.albedo.z) *
                                         1.f);// 0.18f);// /(float)2;
    }
    //hitCol=indirectLightningCol * 1.f;
    //hitCol = ((hitCol / (float)1)+2.f * indirectLightningCol* 0.18f);
    //hitCol = (hitCol + indirectLightningCol) * interObject->mat.albedo;
    hitCol = Vector3f(clamp(0,255,hitCol.x),clamp(0,255,hitCol.y),clamp(0,255,hitCol.z));
    return hitCol;
}

bool sphereTraceShadow(const Ray &ray,const float &maxDist) {
    const float limit = 10e-6;
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

Vector3f reflect(const Vector3f &I, const Vector3f &N)
{
    return I - 2 * I.dotProduct(N) * N;
}

Vector3f uniformSampleHemisphere(const float &r1, const float &r2){
    // cos(theta) = u1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    float sinTheta = sqrtf(1 - r1 * r1);
    float phi = 2 * M_PI * r2;
    float x = sinTheta * cosf(phi);
    float z = sinTheta * sinf(phi);
    return Vector3f(x, r1, z);
}

void createCoordinateSystem(const Vector3f &N, Vector3f &Nt, Vector3f &Nb) {
    if (std::fabs(N.x) > std::fabs(N.y))
        Nt = Vector3f(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z);
    else
        Nt = Vector3f(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
    Nb = N.crossProduct(Nt);
}
