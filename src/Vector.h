//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H
#include <iostream>
#include <cmath>

template<typename T>
class Vector3 {
public:
    T x,y,z;
    Vector3(){
        x=0;
        y=0;
        z=0;
    }
    Vector3(Vector3 const &from){
        this->x=from.x;
        this->y=from.y;
        this->z=from.z;
    }
    explicit Vector3(T x, T y=0, T z=0){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    Vector3 operator=(const Vector3 &vec){
        this->x=vec.x;
        this->y=vec.y;
        this->z=vec.z;
        return *this;
    }

    float mag() const{
        return sqrtf((this->x* this->x) + (this->y * this->y) + (this->z * this->z));
    }
    Vector3<float> normalize(){
        return Vector3(*this / this->mag());
    }

    T dotProduct(const Vector3<T> & vec) const{
        return (x*vec.x + y*vec.y +z*vec.z);
    }

    Vector3<T> crossProduct(const Vector3<T> &v) const
    {
        return Vector3<T>(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x);
    }

    Vector3<T> rotateAround(const char &axis,const float &angle){
        Vector3 tmp;
        switch (axis) {
            case 'x':
                tmp.x=x;
                tmp.y=y*cos(angle) - z*sin(angle);
                tmp.z=y*sin(angle) + z*cos(angle);
                return tmp;
            case 'y':
                tmp.x= (x*cos(angle)) + (z*sin(angle));
                tmp.y=y;
                tmp.z= (-x * sin(angle)) + (z * cos(angle));
                return tmp;
            case 'z':
                tmp.x= (x*cos(angle))-(y*sin(angle));
                tmp.y= (x*sin(angle)) + (y*cos(angle));
                tmp.z=z;
                return tmp;

        }
    }



    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }

    void print() const {
        std::cout<< "{ "<<this->x << ", "<< this->y<< ", "<<this->z<<" }"<< "\n";
    }
};
template<typename T>
Vector3<T> operator+(Vector3<T> from, const Vector3<T>& add) {
    return Vector3(from.x + add.x, from.y + add .y, from.z+add.z);
}
template<typename T>
Vector3<T> operator-(Vector3<T> from, const Vector3<T>& add) {
    return Vector3(from.x - add.x, from.y - add .y, from.z-add.z);
}
template<typename T>
Vector3<T> operator+=(Vector3<T> from ,const Vector3<T> & add) {
    return from + add;
}
template<typename T>
Vector3<T> operator*(T n,const Vector3<T> &vec){
    return Vector3(vec.x*n, vec.y*n, vec.z*n);
}
template<typename T>
Vector3<T> operator*(Vector3<T> vec, const T & n){
    return n*vec;
}
template<typename T>
Vector3<T> operator/(Vector3<T> from, const T& n){
    return Vector3(from.x/n, from.y/n, from.z/n);
}
template<typename T>
float magnitude(const Vector3<T> & vec) {
    return sqrtf((vec.x * vec.x)+(vec.y*vec.y)+(vec.z*vec.z));
}
template<typename T>
Vector3<float> normalize(const Vector3<T> & vec){
    return Vector3(vec / magnitude(vec));
}

template<typename T>
Vector3<T> crossProduct(const Vector3<T>  &a, const Vector3<T> &b)
{
    return Vector3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}

typedef Vector3<float> Position ;
typedef Vector3<float> Vector3f ;
typedef Vector3<int> Vector3i;
#endif //RAYTRACING_VECTOR_H
