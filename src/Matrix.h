//
// Created by adrien on 18/09/2020.
//

#pragma once
#include <cmath>
#include <vector>
#include <iostream>

template<typename T, typename std::size_t s>
class Matrix{
public :
    Matrix(){
        for (uint8_t i = 0; i<s;i++)
            for (uint8_t j = 0;j<s;j++)
                mat[i][j] = 0;
    }

    //specifically for 4 * 4 matrix
    Matrix(const T &a, const T &b, const T &c, const T &d, const T &e, const T &f,
           const T &g, const T &h, const T &i, const T &k, const T &j, const T &l,
           const T &m, const T &n, const T &o, const T &p){
        mat[0][0] = a;
        mat[0][1] = b;
        mat[0][2] = c;
        mat[0][3] = d;
        mat[1][0] = e;
        mat[1][1] = f;
        mat[1][2] = g;
        mat[1][3] = h;
        mat[2][0] = i;
        mat[2][1] = j;
        mat[2][2] = k;
        mat[2][3] = l;
        mat[3][0] = m;
        mat[3][1] = n;
        mat[3][2] = o;
        mat[3][3] = p;
    }

    Matrix(const T value){
        for (uint8_t i = 0; i<s;i++)
            for (uint8_t j = 0;j<s;j++)
                mat[i][j] = value;
    }

    Matrix(const T tab[s]){
        for (uint8_t i = 0; i<s;i++)
            for (uint8_t j = 0;j<s;j++)
                mat[i][j] = tab[i*s+j];
    }

    T valueXY(const T &indexX, const T& indexY){
        return mat[indexX][indexY];
    }

    void identity(){
        for (uint8_t i = 0; i<s;i++)
            for (uint8_t j = 0;j<s;j++)
                mat[i][j] = 0;
        for(uint8_t i=0;i<s;++i)
            mat[i][i] = 1;
    }
/*
    //only for 4*4 matrix and vectors of size 3
    void multVecMatrix(const Vector<T,s> &src, Vector<T,s> &dst) const{
        T divider = 0;
        for(uint8_t i=0;i<3;++i){
            for(uint8_t j=0;j<3;++j){
                dst.vec.at(i) += src.vec.at(i) * mat[j][i];
            }
        }

        for(uint8_t i=0;i<s;++s){
            dst.vec.at(i) = dst.vec.at(i) / divider;
        }
}
*/
    void multDirMatrix(const Vector<T,s> &src, Vector<T,s> &dst) const{
        for(uint8_t i=0;i<s;++i){
            T value = 0;
            for(uint8_t j=0;j<s;++j){
                value += src.vec.at(0) * mat[j][i];
            }
            dst.vec.at(i) = value;
        }
    }

    //only for 4 * 4 matrix only
    void inverse(){
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

    void print(){
        for(uint8_t i=0;i<s;++i){
            for(uint8_t j=0;j<s;++j){
                std::cout<<mat[i][j] << " ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
public :
    T mat[s][s];
};

template<typename T, typename std::size_t s>
Matrix<T,s> operator+(const Matrix<T,s> &mat, const Matrix<T,s> & mat2){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
                temp.mat[i][j] = mat.mat[i][j] + mat2.mat[i][j];
            }
        }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator+(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = mat.mat[i][j] + value;
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator-(const Matrix<T,s> &mat, const Matrix<T,s> & mat2){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = mat.mat[i][j] - mat2.mat[i][j];
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator-(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = mat.mat[i][j] - value;
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator*(const Matrix<T,s> &mat, const Matrix<T,s> & mat2){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            for(uint8_t k=0;k<s;++k){
                temp.mat[i][j] += mat.mat[i][k] * mat2.mat[k][j];
            }
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator*(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
                temp.mat[i][j] = mat.mat[i][j] * value;
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator/(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = mat.mat[i][j] / value;
        }
    }
    return temp;
}

//can only be used for types other than FLOAT and DOUBLES !!!
template<typename T, typename std::size_t s>
Matrix<T,s> operator%(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = mat.mat[i][j] % value;
        }
    }
    return temp;
}

template<typename T, typename std::size_t s>
Matrix<T,s> operator^(const Matrix<T,s> &mat, const T &value){
    Matrix<T,s> temp;
    for(uint8_t i=0;i<s;++i){
        for(uint8_t j=0;j<s;++j){
            temp.mat[i][j] = pow(mat.mat[i][j], value);
        }
    }
    return temp;
}



typedef Matrix<float,2> Matrix2f;
typedef Matrix<float,4> Matrix4f;
