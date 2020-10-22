//
// Created by alban on 08/10/2020.
//

#include "Cube.h"

Cube::Cube() = default;

Cube::Cube(const Vector3f &_corner) : corner(_corner) {}

Cube::~Cube()= default;

bool Cube::intersect(const Ray & ray, float &t){
   /* float t0,t1;
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
        if (t0 < 0) return false; // both t0 and t1 are negative*/

}


void Cube::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const
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



void Cube::print() const {
    std::cout<< "corner = "<<'\n';

}

float Cube::getDistance(const Vector3f &from) const {
#if 0
    // first transform the input point into the object's "object-space".
    float scale = 2.f;

    // this matrix doesn't scale the object
    Matrix44f objectToWorld(0.542903, -0.545887, 0.638172, 0, 0.778733, 0.611711, -0.139228, 0, -0.314374, 0.572553, 0.7572, 0, 0, 1.459974, 0, 1);
    Matrix44f worldToObject = objectToWorld.inverse();
    Vec3f fromObjectSpace = from;
    worldToObject.multVecMatrix(from, fromObjectSpace);

#else
    Vector3f fromObjectSpace = from;
    float scale = 1;

#endif
    //fromObjectSpace *= 1.f / scale;
    fromObjectSpace.x = std::fabs(fromObjectSpace.x);
    fromObjectSpace.y = std::fabs(fromObjectSpace.y);
    fromObjectSpace.z = std::fabs(fromObjectSpace.z);

    // now compute the distance from the point to the neares point on the surface of the object
    Vector3f d = fromObjectSpace - corner;

    Vector3f dmax = d;
    dmax.x = std::max(dmax.x, 0.f);
    dmax.y = std::max(dmax.y, 0.f);
    dmax.z = std::max(dmax.z, 0.f);

    // don't forget to apply the scale back
    //return scale * (std::min(std::max(d.x, std::max(d.y, d.z)), 0.f) + dmax/*.length()*/);

}


