//
// Created by constantin on 11/09/2020.
//

#include "Vector.h"
#include <iostream>

Vector3::Vector3(float x, float y, float z) {
    this->x=x;
    this->y=y;
    this->z=z;
}

Vector3::Vector3() {
    x=0;
    y=0;
    z=0;
}

Vector3::Vector3(Vector3 const &from) {
    this->x=from.x;
    this->y=from.y;
    this->z=from.z;
}

Vector3 Vector3::operator+(Vector3 add) const {
    return Vector3(this->x+add.x,
                    this->y+add.y,
                    this->z+add.z);
}

Vector3 Vector3::operator+=(const Vector3 &add) {
    this->x+=add.x;
    this->y+=add.y;
    this->z+=add.z;
    return *this;
}

Vector3 Vector3::operator*(const float n) {
    this->x*=n;
    this->y*=n;
    this->z*=n;
    return *this;
}

void Vector3::print() {
    std::cout<< "{ "<<this->x << ", "<< this->y<< ", "<<this->z<<" }";
}

Vector3 Vector3::operator=(Vector3 vec) {
    this->x= vec.x;
    this->y= vec.y;
    this->z= vec.z;
    return *this;
}


Vector3 operator*(float n, Vector3 &vec) {
    return vec*n;
}
