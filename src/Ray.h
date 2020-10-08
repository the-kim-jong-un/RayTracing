//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Vector.h"
#include "Object.h"
class Object;

class Ray {
public:
    Position origin;
    Vector3f direction;
    Ray();
    Ray(const Position & position, const Vector3f & direction);
};

Vector3f sphereTrace(const Ray &ray,const unsigned int & depth, Vector3f &dBuffer);
Vector3f stepColoring(const unsigned int& steps);
bool traceRay(const Ray &ray, float &inter, Object *& hitObj);
Vector3f castRay(const Ray& ray);
Vector3f shade(const Ray &ray, const float &t, Object * interObject,const unsigned int & depth);
Vector3f reflect(const Vector3f &I, const Vector3f &N);
bool sphereTraceShadow(const Ray &ray,const float &maxDist);
Vector3f uniformSampleHemisphere(const float &r1, const float &r2);
void createCoordinateSystem(const Vector3f &N, Vector3f &Nt, Vector3f &Nb);


#endif //RAYTRACING_RAY_H
