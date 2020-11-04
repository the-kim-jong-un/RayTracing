//
// Created by constantin on 12/09/2020.
//

#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H


#include "Vector.h"




class Renderer {
public:

    enum RenderMode{
        MONO,
        MULTI
    };
    enum TraceMode{
        RAYTRACING,
        SPHERETRACING
    };

    unsigned int width;
    unsigned int height;
    const unsigned int maxThread = 32;
    static float far;
    static float near;
    static const unsigned int sampleAcuracy = 128;
    static const unsigned int maxSampleDepth = 0;
    static const unsigned int maxDepth = 2;
    static RenderMode renderMode;
    static TraceMode traceMode;
    static Vector3f backgroundColor;

    ///\brief Crée le rendu à enregistrer
    Renderer(const int & width, const int& height,const Vector3f & BG=Vector3f(200,200,200),const RenderMode & =MONO, const TraceMode & = RAYTRACING);
    void render();
    void renderMono();
    void renderThread();

    void threadRayCast(Vector3f *framebuffer,const Vector3f & origin, const float & fov, const float &ratio, const unsigned int & offset) const;

    ///\brief Enregistre la scène dans un fichier
    void saveToFile(const Vector3f * frameBuffer,const int &offset=0);

private:
    int imagecount=0;
    Vector3f * frameBuffer;
    Vector3f * depthBuffer;

};

inline float clamp(const float & low, const float & high, const float &val);
float deg2rad(const float &deg);


#endif //RAYTRACING_RENDERER_H
