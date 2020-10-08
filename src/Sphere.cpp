//
// Created by constantin on 11/09/2020.
//

#include "Sphere.h"

bool Sphere::intersect(const Ray & ray, float &t){
    float t0,t1;
    Vector3f tmp= position - ray.origin;
    float radius2 = radius*radius;
    float tca = tmp.dotProduct(ray.direction);
    if (tca <0) {
        return false;
    }
    float d2 = tmp.dotProduct(tmp) - tca * tca;
    if (d2 > radius2) return false;
    float thc = sqrtf(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }

    t = t0;
    return true;
}

Sphere::~Sphere(){

}

Sphere::Sphere() {
    position=Vector3f();
    radius=.3;
}

void Sphere::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const
{
    Nhit = Phit - position;
    Nhit.normalize();
    // In this particular case, the normal is simular to a point on a unit sphere
    // centred around the origin. We can thus use the normal coordinates to compute
    // the spherical coordinates of Phit.
    // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
    // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
    tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5;
    tex.y = acosf(Nhit.y) / M_PI;
}

Sphere::Sphere(const Vector3f& pos,const float & radius, const Material & material) {
    position=pos;
    this->color=Vector3f();
    mat=material;
    this->radius=radius;
}

void Sphere::print() const {
    std::cout<<"radius = "<<radius<<'\n';

}

float Sphere::getDistance(const Vector3f &from) const {
    return magnitude(from - position)-radius;
}


