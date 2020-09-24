//
// Created by constantin on 12/09/2020.
//

#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include "immintrin.h"
#include <thread>
#include <iostream>
#include <ostream>
#include <fstream>

Renderer::Renderer(const int &width, const int &height,const Vector3f & BG, const RenderMode &r, const TraceMode & t) {
    this->width=width;
    this->height=height;
    backgroundColor=BG;
    renderMode = r;
    traceMode=t;
}

void Renderer::renderMono() {
    Vector3f origin;
    float fov = tanf(deg2rad(Camera::fov*0.5f));
    float ratio = (float)width/(float)height;
    frameBuffer = new Vector3f[width*height];
    Vector3f * pix = frameBuffer;
    Camera::cameraToWorld.multVecMatrix(Vector3f(),origin);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2 * ((float)i + 0.5f) / (float)width - 1) * fov;
            float y = (1 - 2 * ((float)j + 0.5f) / (float)height) * fov * (1/ratio);

            Vector3f dir;
            Camera::cameraToWorld.multDirMatrix(Vector3f (x,y,-1).normalize(),dir);
            dir=normalize(dir);
            unsigned int ind =j*width+i;
            if (traceMode==RAYTRACING){
                pix[ind]=castRay(Ray(origin,dir));
            } else{
                Vector3f colBuff = Vector3f();
                int maxRay = 1;
                for (int rayn = 0; rayn < maxRay; ++rayn) {
                    colBuff = colBuff+ sphereTrace(Ray(origin,dir));
                }
                colBuff = colBuff/(float)maxRay;
                pix[ind]=colBuff;
            }
        }
    }

    saveToFile(pix);
    delete [] pix;
}

void Renderer::renderThread() {
    Vector3f origin;
    float fov = tanf(deg2rad(Camera::fov*0.5f));
    float ratio = (float)width/(float)height;
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

void Renderer::threadRayCast(Vector3f *framebuffer,const Vector3f & origin, const float & fov, const float &ratio,const unsigned int & offset) const {
    for (int j = 0; j < height; ++j) {
        for (unsigned int i = offset*(width/maxThread); i < (offset+1)*(width/maxThread); ++i) {
            float x = (2 * ((float)i + 0.5f) / (float)width - 1) * fov;
            float y = (1 - 2 * ((float)j + 0.5f) / (float)height) * fov * (1/ratio);
            Vector3f dir;
            Camera::cameraToWorld.multDirMatrix(Vector3f (x,y,-1),dir);
            dir=normalize(dir);
            unsigned int ind =j*width+i;
            if (traceMode==RAYTRACING){
                framebuffer[ind]=castRay(Ray(origin,dir));
            } else{
                Vector3f colBuff = Vector3f();
                int maxRay = 1;
                for (int rayn = 0; rayn < maxRay; ++rayn) {
                    colBuff = colBuff+ sphereTrace(Ray(origin,dir));
                }
                colBuff = colBuff/(float)maxRay;
                framebuffer[ind]=colBuff;
            }
        }
    }
}


void Renderer::saveToFile(const Vector3f *frameBuffer) {
    int count = imagecount;
    auto start = std::chrono::steady_clock::now();     // start timer

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
    auto end = std::chrono::steady_clock::now();
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
float deg2rad(const float &deg) {
    return deg * (float)M_PI / 180.0f;
}
