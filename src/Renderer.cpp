//
// Created by constantin on 12/09/2020.
//

#include "Renderer.h"
#include "SceneManager.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>

Renderer::Renderer(const int &width, const int &height,const Vector3f & BG) {
    this->width=width;
    this->height=height;

    frameBuffer = new Vector3f[width*height];
}


void Renderer::render() {

}

inline
float clamp(const float & low, const float & high, const float &val){
    return std::max(low, std::min(high,val));
}

inline
float deg2rad(const float &deg)
{ return deg * M_PI / 180; }
