//
// Created by constantin on 12/09/2020.
//

#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>

Renderer::Renderer(const int &width, const int &height,const Vector3f & BG) {
    this->width=width;
    this->height=height;
    backgroundColor=BG;
    frameBuffer = new Vector3f[width*height];
}


void Renderer::render() {
    Vector3f origin;
    float fov = tan(deg2rad(Camera::fov*0.5));
    float ratio = width/height;
    Vector3f * pix = frameBuffer;
    Camera::cameraToWorld.multVecMatrix(Vector3f(),origin);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2 * (i + 0.5) / (float)width - 1) * fov;
            float y = (1 - 2 * (j + 0.5) / (float)height) * fov * (1/ratio);

            Vector3f dir;
            Camera::cameraToWorld.multDirMatrix(Vector3f (x,y,-1),dir);
            dir=normalize(dir);
            int ind =j*height+i;
            pix[ind]=castRay(Ray(origin,dir));
            if (j==height/2 && i ==width/2) {

                std::cout << "50% done"<< '\n';
            }
        }
    }

    std::ofstream ofs("../data/render.ppm", std::ios::out);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width*height; ++i) {
        /*
        char r = (char)(255 * clamp(0, 1, (float)pix[i].x));
        char g = (char)(255 * clamp(0, 1, pix[i].y));
        char b = (char)(255 * clamp(0, 1, pix[i].z));*/
        char r= (char)(int)pix[i].x;
        char g= (char)(int)pix[i].y;
        char b= (char)(int)pix[i].z;
        ofs << r << g << b;
    }
    ofs.close();
}

inline
float clamp(const float & low, const float & high, const float &val){
    return std::max(low, std::min(high,val));
}

inline
float deg2rad(const float &deg)
{ return deg * M_PI / 180; }
