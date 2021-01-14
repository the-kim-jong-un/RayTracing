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

Vector3f sphereTrace(const Ray &ray, const unsigned int &depth, Vector3f &dBuffer, Vector3f &pBuffer) {
    const float maxDist=128.0f;
    float minDist;
    const double limit=15e-5;
    float t=0;
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
        if(minDist<0){
            minDist *= -1;
        }
        if (minDist<= limit*t){
            dBuffer=Vector3f(1,1,1)*t;
            return shade(ray, t, interObject, depth, pBuffer);// /(float)((255 - steps)/255);
        }
        t+=minDist;
        ++steps;
    }
    dBuffer=Vector3f(1,1,1)*(maxDist);
    return Renderer::backgroundColor;
}

Vector3f stepColoring(const unsigned int &steps) {

    float greyscale=255 - clamp(0,255,steps*6);
    return Vector3f(greyscale,greyscale,greyscale);
}

Vector3f shade(const Ray &ray, const float &t, Object *interObject, const unsigned int &depth, Vector3f &pBuffer) {
    const float delta= 10e-6;
    Vector3f p= ray.origin+t*ray.direction; ///Point de contact
    Vector3f norm=Vector3f (
            interObject->getDistance(p+Vector3f(delta)) - interObject->getDistance(p+Vector3f(-delta)),
            interObject->getDistance(p+Vector3f(0,delta)) - interObject->getDistance(p+Vector3f(0,-delta)),
            interObject->getDistance(p+Vector3f(0,0,delta)) - interObject->getDistance(p+Vector3f(0,0,-delta))
            ); ///Normale au point de contact
    norm=normalize(norm);
    Vector3f hitCol= Vector3f();
    Vector3f diffuse;
    Vector3f specular=Vector3f();
    Vector3f reflection;
    Vector3f refraction;
    Vector3f indirectLightningCol;

    ///Calcul de la couleur de base
    for(auto light : SceneManager::lights){
        Vector3f lightDir=light->origin - p;
        if (lightDir.dotProduct(norm)>0){
            float dist2= lightDir.norm();
            lightDir= normalize(lightDir);
            bool shadow = 1 - sphereTraceShadow(Ray(p,lightDir), sqrtf(dist2));
            diffuse= diffuse+ (float)shadow * interObject->mat.albedo * light->intensity * std::max(0.f,norm.dotProduct(1.0f*lightDir));
            Vector3f R= reflect(lightDir,norm);
            float tmp= (float)shadow* light->intensity * std::pow(std::max(0.f,R.dotProduct(1.f*ray.direction)),interObject->mat.n);
            specular= specular + Vector3f(tmp,tmp,tmp);
        }

        Vector3f R= reflect(ray.direction,norm);
        Vector3f tbuff;
        reflection= reflection + (sphereTrace(Ray(p, R), depth + 1, tbuff, tbuff));
        Vector3f tmpdiff=Vector3f(diffuse.x, diffuse.y, diffuse.z);
        Vector3f tmpspec=Vector3f(specular.x,specular.y,specular.z);
        reflection = reflection / ((float)Renderer::maxDepth);
        hitCol = tmpdiff * interObject->mat.matDiffuse + tmpspec * interObject->mat.matSpecular + reflection * interObject->mat.matReflection;
    }

    /// Calcul de la Global Illumination
    if (depth < Renderer::maxSampleDepth){
        Vector3f Nt,Nb;
        createCoordinateSystem(norm,Nt,Nb);
        float pdf = 1 / (1 * M_PI);
        for (int n = 0; n < Renderer::sampleAccuracy; ++n) { ///Monte Carlo
            float r1 = distribution(generator);
            float r2 = distribution(generator);
            Vector3f sample = uniformSampleHemisphere(r1, r2);
            Vector3f sampleWorld(
                    sample.x * Nb.x + sample.y * norm.x + sample.z * Nt.x,
                    sample.x * Nb.y + sample.y * norm.y + sample.z * Nt.y,
                    sample.x * Nb.z + sample.y * norm.z + sample.z * Nt.z);
            Vector3f tbuff;
            indirectLightningCol = indirectLightningCol + (r1 * sphereTrace(Ray(p + sampleWorld * 0.001f, sampleWorld),
                                                                            depth + 1, tbuff, tbuff) / pdf);
        }
    }
    indirectLightningCol = indirectLightningCol /(float)Renderer::sampleAccuracy;
    //pBuffer = Vector3f(clamp(0,255,indirectLightningCol.x),clamp(0,255,indirectLightningCol.y),clamp(0,255,indirectLightningCol.z));
    pBuffer = clamp(0,255,indirectLightningCol);
    if (Renderer::sampleAccuracy > 0) {
        hitCol = ((hitCol / (float) 1.2) + 1.f * Vector3f(indirectLightningCol.x * interObject->mat.albedo.x,
                                                        indirectLightningCol.y * interObject->mat.albedo.y,
                                                        indirectLightningCol.z * interObject->mat.albedo.z) *
                                         2.f);// 0.18f);// /(float)2;
    }


    ///Calcul de la Refraction
    float KR;
    float ior = interObject->mat.matRefraction;
    fresnel(ray.direction,norm,ior,KR);
    bool outside = ray.direction.dotProduct(norm)<0;
    Vector3f bias = 0.01f * norm;
    if (KR < 1) {
        Vector3f refracDir =refract(ray.direction, norm,ior).normalize();
        Vector3f refracRayOrig = outside ? p - bias : p + bias;
        Vector3f tBuff;
        refraction = sphereTrace(Ray(refracRayOrig, refracDir), depth + 1, tBuff, tBuff);
    }
    hitCol = hitCol * KR + refraction* (1-KR);
    //hitCol = Vector3f(clamp(0,255,hitCol.x),clamp(0,255,hitCol.y),clamp(0,255,hitCol.z));
    hitCol = clamp(0,255,hitCol);
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

Vector3f reflect(const Vector3f &I, const Vector3f &N)
{
    return I - 2 * I.dotProduct(N) * N;
}

Vector3f uniformSampleHemisphere(const float &r1, const float &r2){
    float sinTheta = sqrtf(1 - r1 * r1);
    float phi = 2.f * M_PI * r2;
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

Vector3f refract(const Vector3f &I, const Vector3f &N, const float & ior) {
    float cosi = clamp(-1.0,1.0,I.dotProduct(N));
    float etai=1,etat=ior;
    Vector3f n = N;
    if(cosi < 0) {
        cosi = -cosi;
    } else{
        std::swap(etai,etat);
        n=-1.f*N;
    }
    float et= etai/etat;
    float k = 1 - (et * et * (1- cosi * cosi));
    return k<0 ? Vector3f() : et * I + (et* cosi - std::sqrt(k))*n;
}

void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr)
{
    float cosi = clamp(-1, 1, I.dotProduct(N));
    float etai = 1;
    float etat = ior;
    if (cosi > 0) { std::swap(etai, etat); }
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    if (sint >= 1) {
        kr = 1;
    }
    else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
}
