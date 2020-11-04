//
// Created by constantin on 12/09/2020.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H


#include "Vector.h"
#include "Matrix4x4.h"

class Camera {
public:
    Position origin;
    static float fov;
    static Matrix4x4 cameraToWorld;

    ///\brief Regle la camera
    ///\param from : position de la camera
    ///\param to : endroit visé par la camera
    ///\param dir : Indique le haut de la scène
    static Matrix4x4 lookAt(const Vector3<float> & from, const Vector3<float> & to,const Vector3f & dir=Vector3f(0,1,0));
};


#endif //RAYTRACING_CAMERA_H
