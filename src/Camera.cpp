//
// Created by constantin on 12/09/2020.
//

#include "Camera.h"

Matrix4x4 Camera::lookAt(Vector3<float> from, Vector3<float> to, Vector3f dir) {
    {
        Vector3f forward = normalize(from - to);
        Vector3f right = crossProduct(normalize(dir), forward);
        Vector3f up = crossProduct(forward, right);

        Matrix4x4 camToWorld;

        camToWorld[0][0] = right.x;
        camToWorld[0][1] = right.y;
        camToWorld[0][2] = right.z;
        camToWorld[1][0] = up.x;
        camToWorld[1][1] = up.y;
        camToWorld[1][2] = up.z;
        camToWorld[2][0] = forward.x;
        camToWorld[2][1] = forward.y;
        camToWorld[2][2] = forward.z;

        camToWorld[3][0] = from.x;
        camToWorld[3][1] = from.y;
        camToWorld[3][2] = from.z;

        return camToWorld;
    }
}
