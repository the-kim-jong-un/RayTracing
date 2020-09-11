//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H


class Vector3 {
public:
    float x,y,z;
    Vector3();
    Vector3(Vector3 const &from);
    explicit Vector3(float x, float y=0, float z=0);
    Vector3 operator+(Vector3 add) const;
    Vector3 operator*(const float n);
    Vector3 operator=(const Vector3 vec);
    Vector3 operator+=(const Vector3 & add);
    void print();
};

Vector3 operator*(float n, Vector3 &vec);

#endif //RAYTRACING_VECTOR_H
