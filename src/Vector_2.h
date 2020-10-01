//
// Created by adrien on 16/09/2020.
//

#pragma once

#include <cmath>
#include <vector>
#include <iostream>

template<typename T, typename std::size_t s>
class Vector{
public :
    Vector(){
    vec.reserve(s);
        for(uint8_t i=0;i<s;++i){
            vec.push_back(0);
        }
    }

    Vector(const Vector<T,s> &from){
        vec.reserve(s);
        for(uint8_t i=0;i<s;++i){
            vec.push_back(from.vec.at(i));
        }
    }

    Vector(const T tab[s]){
        vec.reserve(s);
        for(uint8_t i=0;i<s;++i){
            vec.push_back(tab[i]);
        }
    }

    //specifically for 3 dimensional vector
    Vector(const T X,const T Y=0,const T Z=0){
        vec.reserve(3);
        vec.push_back(X);
        vec.push_back(Y);
        vec.push_back(Z);
    }

    Vector operator=(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) = vec2.vec.at(i);
        }
        return *this;
    }

    bool operator==(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            if(vec.at(i) != vec2.vec.at(i))
                return false;
        }
        return true;
    }

    Vector operator+(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) += vec2.vec.at(i);
        }
        return *this;
    }

    Vector operator+(const T &value){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) += value;
        }
        return *this;
    }

    Vector operator-(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) -= vec2.vec.at(i);
        }
        return *this;
    }

    Vector operator-(const T &value){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) -= value;
        }
        return *this;
    }

    Vector operator*(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) = vec.at(i) * vec2.vec.at(i);
        }
        return *this;
    }

    Vector operator*(const T &value){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) *= value;
        }
        return *this;
    }

    //ain't checking division by zero CAREFUL
    Vector operator/(const T &value){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) /= value;
        }
        return *this;
    }

    //ain't checking division by zero CAREFUL
    Vector operator/(const Vector<T,s> &vec2){
        for(std::size_t i=0;i<vec.size();++i){
            vec.at(i) = vec.at(i) / vec2.vec.at(i);
        }
        return *this;
    }

    //only for 3 dimensional vectors
    T magnitude() const{
        return std::sqrt((vec.at(0)* vec.at(0)) + (vec.at(1) * vec.at(1)) + (vec.at(2) * vec.at(2)));
    }

    //only for 3 dimensional vectors
    T dotProduct(const Vector<T,s> &vec2) const{
        return (vec.at(0) * vec2.vec.at(0) + vec.at(1) * vec2.vec.at(1) + vec.at(2) * vec2.vec.at(2));
    }

    //only for 3 dimensional vectors
    Vector crossProduct(const Vector<T,s> &vec2) const{
        return Vector<T,s>(
                vec.at(1) * vec2.vec.at(2) - vec.at(2) * vec2.vec.at(1),
                vec.at(2) * vec2.vec.at(0) - vec.at(0) * vec2.vec.at(2),
                vec.at(0) * vec2.vec.at(1) - vec.at(1) * vec2.vec.at(0));
    }

    //only for 3 dimensional float vectors
    Vector rotateAround(const char &axis, const float &angle){
        Vector<float,3> tmp;
        switch(axis){
            case 'x':
                tmp.vec.at(0) = vec.at(0);
                tmp.vec.at(0) = vec.at(1) * cos(angle) - vec.at(2) * sin(angle);
                tmp.vec.at(0) = vec.at(1) * sin(angle) + vec.at(2) * cos(angle);
                return tmp;
            case 'y':
                tmp.vec.at(0) = (vec.at(0) * cos(angle)) + (vec.at(2)*sin(angle));
                tmp.vec.at(0) = vec.at(1);
                tmp.vec.at(0) = (-vec.at(2) * sin(angle)) + (vec.at(2) * cos(angle));
                return tmp;
            case 'z':
                tmp.vec.at(0) = (vec.at(0) * cos(angle)) - (vec.at(1) * sin(angle));
                tmp.vec.at(0) = (vec.at(0) * sin(angle)) + (vec.at(1) * cos(angle));
                tmp.vec.at(0) = vec.at(2);
                return tmp;
            default :
                //catch exception
                break;
        }
    }

    T distanceX(const Vector<T,s> &vec2) const{
        return abs(vec.at(0) - vec2.vec.at(0));
    }

    //ain't checking if accessing Y axis exist
    T distanceY(const Vector<T,s> &vec2) const{
        return abs(vec.at(1) - vec2.vec.at(1));
    }

    //ain't checking if accessing Z axis exist
    T distanceZ(const Vector<T,s> &vec2) const{
        return abs(vec.at(2) - vec2.vec.at(2));
    }

    //ain't checking if accessing axis which is too big
    T distance(const Vector<T,s> &vec2, const std::size_t axis) const{
        return abs(vec.at(axis) - vec2.vec.at(axis));
    }

    void print(){
        for(uint8_t i=0;i<vec.size();++i){
            std::cout<<vec.at(i)<<" ";
        }
        std::cout<<std::endl;
    }

public :
    std::vector<T> vec;
};

template<typename T, typename std::size_t s>
Vector<T,s> operator+(Vector<T,s> from, Vector<T,s> & add){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) + add.vec.at(i);
    }
    return temp;
}

template<typename T, typename std::size_t s>
Vector<T,s> operator-(Vector<T,s> from, Vector<T,s> & add){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) - add.vec.at(i);
    }
    return temp;
}

template<typename T, typename std::size_t s>
Vector<T,s> operator*(Vector<T,s> from, Vector<T,s> & add){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) * add.vec.at(i);
    }
    return temp;
}

template<typename T, typename std::size_t s>
Vector<T,s> operator*(Vector<T,s> from, const T & value){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) * value;
    }
    return temp;
}

template<typename T, typename std::size_t s>
Vector<T,s> operator/(Vector<T,s> from, Vector<T,s> & add){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) / add.vec.at(i);
    }
    return temp;
}

template<typename T, typename std::size_t s>
Vector<T,s> operator/(Vector<T,s> from, const T & value){
    Vector<T,s> temp;
    for(std::size_t i=0;i<s;++i){
        temp.vec.at(i) = from.vec.at(i) / value;
    }
    return temp;
}

//only for 3 dimensional vectors
template<typename T, typename std::size_t s>
T magnitude(Vector<T,s> from) {
    return std::sqrt((from.at(0) * from.at(0)) + (from.at(1) * from.at(1)) + (from.at(2) * from.at(2)));
}

//only for 3 dimensional vectors
template<typename T, typename std::size_t s>
Vector<T,s> crossProduct(const Vector<T,s> &from, const Vector<T,s> &from2) {
    return Vector<T,s>(
            from.at(1) * from2.vec.at(2) - from.at(2) * from2.vec.at(1),
            from.at(2) * from2.vec.at(0) - from.at(0) * from2.vec.at(2),
            from.at(0) * from2.vec.at(1) - from.at(1) * from2.vec.at(0));
}

typedef Vector<float,3> Vector3f;
typedef Vector<float,3> Position;

