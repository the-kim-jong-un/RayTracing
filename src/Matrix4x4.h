//
// Created by constantin on 12/09/2020.
//

#ifndef RAYTRACING_MATRIX4X4_H
#define RAYTRACING_MATRIX4X4_H


#include "Vector.h"

class Matrix4x4 {
public:
    float x[4][4];
    Matrix4x4();
    Matrix4x4(float a, float b, float c, float d, float e, float f, float g, float h,
            float i, float j, float k, float l, float m, float n, float o, float p);


    ~Matrix4x4();

    static void multiply(const Matrix4x4& mat, const Matrix4x4 & mult, Matrix4x4 & to);

    const float* operator [] (int i) const { return x[i]; }
    float * operator [] (int i) { return x[i]; }
    Matrix4x4 inverse();
    Matrix4x4 invert();

    void multVecMatrix(const Vector3<float> &src, Vector3<float> &dst) const;
    void multDirMatrix(const Vector3f &src, Vector3f &dst) const;
};

Matrix4x4 operator*(Matrix4x4 a, const  Matrix4x4&b);

#endif //RAYTRACING_MATRIX4X4_H
