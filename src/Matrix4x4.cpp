//
// Created by constantin on 12/09/2020.
//

#include "Matrix4x4.h"
#include "Vector.h"

Matrix4x4::Matrix4x4() {
    x[0][0] = 1;
    x[0][1] = 0;
    x[0][2] = 0;
    x[0][3] = 0;
    x[1][0] = 0;
    x[1][1] = 1;
    x[1][2] = 0;
    x[1][3] = 0;
    x[2][0] = 0;
    x[2][1] = 0;
    x[2][2] = 1;
    x[2][3] = 0;
    x[3][0] = 0;
    x[3][1] = 0;
    x[3][2] = 0;
    x[3][3] = 1;
}

Matrix4x4::~Matrix4x4() {

}

Matrix4x4::Matrix4x4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k,
                     float l, float m, float n, float o, float p){
    x[0][0] = a;
    x[0][1] = b;
    x[0][2] = c;
    x[0][3] = d;
    x[1][0] = e;
    x[1][1] = f;
    x[1][2] = g;
    x[1][3] = h;
    x[2][0] = i;
    x[2][1] = j;
    x[2][2] = k;
    x[2][3] = l;
    x[3][0] = m;
    x[3][1] = n;
    x[3][2] = o;
    x[3][3] = p;
}

void Matrix4x4::multiply(const Matrix4x4 &mat, const Matrix4x4 &mult, Matrix4x4 &to) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            to[i][j] = mat[i][0] * mult[0][j] + mat[i][1] * mult[1][j] +
                      mat[i][2] * mult[2][j] + mat[i][3] * mult[3][j];
        }
    }
}

Matrix4x4 Matrix4x4::inverse()
{
    int i, j, k;
    Matrix4x4 s;
    Matrix4x4 t (*this);

    // Forward elimination
    for (i = 0; i < 3 ; i++) {
        int pivot = i;

        float pivotsize = t[i][i];

        if (pivotsize < 0)
            pivotsize = -pivotsize;

        for (j = i + 1; j < 4; j++) {
            float tmp = t[j][i];

            if (tmp < 0)
                tmp = -tmp;

            if (tmp > pivotsize) {
                pivot = j;
                pivotsize = tmp;
            }
        }

        if (pivotsize == 0) {
            // Cannot invert singular matrix
            return Matrix4x4();
        }

        if (pivot != i) {
            for (j = 0; j < 4; j++) {
                float tmp;

                tmp = t[i][j];
                t[i][j] = t[pivot][j];
                t[pivot][j] = tmp;

                tmp = s[i][j];
                s[i][j] = s[pivot][j];
                s[pivot][j] = tmp;
            }
        }

        for (j = i + 1; j < 4; j++) {
            float f = t[j][i] / t[i][i];

            for (k = 0; k < 4; k++) {
                t[j][k] -= f * t[i][k];
                s[j][k] -= f * s[i][k];
            }
        }
    }

    // Backward substitution
    for (i = 3; i >= 0; --i) {
        float f;

        if ((f = t[i][i]) == 0) {
            // Cannot invert singular matrix
            return Matrix4x4();
        }

        for (j = 0; j < 4; j++) {
            t[i][j] /= f;
            s[i][j] /= f;
        }

        for (j = 0; j < i; j++) {
            f = t[j][i];

            for (k = 0; k < 4; k++) {
                t[j][k] -= f * t[i][k];
                s[j][k] -= f * s[i][k];
            }
        }
    }

    return s;
}

Matrix4x4 Matrix4x4::invert() {
    *this = inverse();
    return *this;
}

Matrix4x4 operator*(Matrix4x4 a, const Matrix4x4 &b) {
    Matrix4x4 tmp;
    Matrix4x4::multiply(a, b, tmp);

    return tmp;
}


void Matrix4x4::multVecMatrix(const Vector3f &src, Vector3f &dst) const
{
    float a, b, c, w;

    a = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0] + x[3][0];
    b = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1] + x[3][1];
    c = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2] + x[3][2];
    w = src[0] * x[0][3] + src[1] * x[1][3] + src[2] * x[2][3] + x[3][3];

    dst.x = a / w;
    dst.y = b / w;
    dst.z = c / w;
}

void Matrix4x4::multDirMatrix(const Vector3f &src, Vector3f &dst) const
{
    float a, b, c;

    a = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0];
    b = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1];
    c = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2];

    dst.x = a;
    dst.y = b;
    dst.z = c;
}
