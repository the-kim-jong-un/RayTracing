//
// Created by constantin on 12/09/2020.
//

#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include "immintrin.h"
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>

Renderer::Renderer(const int &width, const int &height,const Vector3f & BG, const RenderMode &r) {
    this->width=width;
    this->height=height;
    backgroundColor=BG;
    renderMode = r;
}


void Renderer::renderMono() {
    Vector3f origin;
    float fov = tan(deg2rad(Camera::fov*0.5));
    float ratio = width/(float)height;
    frameBuffer = new Vector3f[width*height];
    Vector3f * pix = frameBuffer;
    Camera::cameraToWorld.multVecMatrix(Vector3f(),origin);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2 * (i + 0.5) / (float)width - 1) * fov;
            float y = (1 - 2 * (j + 0.5) / (float)height) * fov * (1/ratio);

            Vector3f dir;
            Camera::cameraToWorld.multDirMatrix(Vector3f (x,y,-1),dir);
            dir=normalize(dir);
            unsigned int ind =j*width+i;
            pix[ind]=castRay(Ray(origin,dir));
        }
    }

    saveToFile(pix);
    delete [] pix;

}

void Renderer::renderThread() {
    int sectionWidth= width/32;

    Vector3f origin;
    float fov = tan(deg2rad(Camera::fov*0.5));
    float ratio = width/height;
    frameBuffer = new Vector3f[width*height];
    Vector3f * pix = frameBuffer;
    Camera::cameraToWorld.multVecMatrix(Vector3f(),origin);

    std::thread tPool[maxThread];
    for (int j = 0; j < maxThread; ++j) {
        tPool[j]=std::thread(&Renderer::threadRayCast,this,
             pix,
             origin,
             fov,
             ratio,
             j);
    }

    for (int i = 0; i < maxThread; ++i) {
        tPool[i].join();
    };
    saveToFile(pix);
    delete [] pix;
}

void Renderer::threadRayCast(Vector3f *framebuffer,const Vector3f & origin, const float & fov, const float &ratio,const unsigned int & offset) {
    for (int j = 0; j < height; ++j) {
        for (int i = offset*(width/maxThread); i < (offset+1)*(width/maxThread); ++i) {
            float x = (2 * (i + 0.5) / (float)width - 1) * fov;
            float y = (1 - 2 * (j + 0.5) / (float)height) * fov * (1/ratio);
            Vector3f dir;
            Camera::cameraToWorld.multDirMatrix(Vector3f (x,y,-1),dir);
            dir=normalize(dir);
            unsigned int ind =j*width+i;
            framebuffer[ind]=castRay(Ray(origin,dir));
        }
    }
}


void Renderer::saveToFile(const Vector3f *frameBuffer) {
    int count = imagecount;
    std::chrono::steady_clock sc;   // create an object of `steady_clock` class
    auto start = sc.now();     // start timer

    std::ofstream ofs("../data/render" + std::to_string(imagecount) +".ppm", std::ios::out);
    ++imagecount;
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < width*height; ++i) {
        char r= (char)(int)frameBuffer[i].x;
        char g= (char)(int)frameBuffer[i].y;
        char b= (char)(int)frameBuffer[i].z;
        ofs << r << g << b;
    }
    ofs.close();
    auto end = sc.now();
    auto time_span = static_cast<std::chrono::duration<double>>(end - start);   // measure time span between start & end
    std::cout<<"Image " << count<< " saved in: "<<time_span.count()<<" seconds"<<'\n';
}

void Renderer::render() {
    switch (renderMode) {
        case MONO:
            renderMono();
            break;
        case MULTI:
            renderThread();
            break;
    }
}


inline
float clamp(const float & low, const float & high, const float &val){
    return std::max(low, std::min(high,val));
}

inline
float deg2rad(const float &deg)
{ return deg * M_PI / 180; }
