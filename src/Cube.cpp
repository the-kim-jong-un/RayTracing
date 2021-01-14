//
// Created by alban on 08/10/2020.
//

#include "Cube.h"

Cube::Cube() = default;

Cube::Cube(const Vector3f &_corner) : corner(_corner) {}

Cube::~Cube()= default;

bool Cube::intersect(const Ray & ray, float &t){
 return false;
}


void Cube::getSurfaceData(const Vector3f &Phit, Vector3f &Nhit, Vector3f &tex) const
{
    Nhit = Phit - position;
    Nhit.normalize();
    tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5;
    tex.y = acosf(Nhit.y) / M_PI;
}



void Cube::print() const {
    std::cout<< "corner = ";
    corner.print() ;

}

float Cube::getDistance(const Vector3f &from) const {
    Vector3f fromObjectSpace = (from-position).rotateAround('x',rotation.x)
            .rotateAround('y',rotation.y)
            .rotateAround('z',rotation.z);
    float scale = 1;
    fromObjectSpace = fromObjectSpace * (1.f / scale);
    fromObjectSpace.x = std::fabs(fromObjectSpace.x);
    fromObjectSpace.y = std::fabs(fromObjectSpace.y);
    fromObjectSpace.z = std::fabs(fromObjectSpace.z);
    Vector3f d = fromObjectSpace - corner;

    Vector3f dmax = d;
    dmax.x = std::max(dmax.x, 0.f);
    dmax.y = std::max(dmax.y, 0.f);
    dmax.z = std::max(dmax.z, 0.f);
    return scale * (std::min(std::max(d.x, std::max(d.y, d.z)), 0.f) + dmax.mag());

}


