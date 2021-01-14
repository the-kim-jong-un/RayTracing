//
// Created by constantin on 12/09/2020.
//

#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H


#include "Vector.h"
#include "mainwindow.h"



class Renderer {
public:

    static Renderer * self;

    enum RenderMode{
        MONO,
        MULTI
    };
    enum TraceMode{
        RAYTRACING,
        SPHERETRACING
    };

    static unsigned int width;
    static unsigned int height;
    const unsigned int maxThread = 32;
    static float far;
    static float near;
    static unsigned int sampleAccuracy;
    static const unsigned int maxSampleDepth = 1;
    static const unsigned int maxDepth = 2;
    static RenderMode renderMode;
    static TraceMode traceMode;
    static Vector3f backgroundColor;
    static bool running;
    static MainWindow * mw;
    static QByteArray * Qarr;

    ///\brief Constructeur du Renderer
    /// @param width Longueur de l'image
    /// @param height Largeur de l'image
    /// @param BG Couleur de fond
    Renderer(const int & width, const int& height,const Vector3f & BG=Vector3f(200,200,200),const RenderMode & =MONO, const TraceMode & = RAYTRACING);
    void render();

    /// @brief Lance le rendu en mono thread
    /// @warning NE PAS UTILISER
    void renderMono();

    /// @brief Lance le rendu en multi thread
    void renderThread();

    /// @brief Fonction de lancement de rayon, optimiser pour l'utilisation en thread
    void threadRayCast(Vector3f *framebuffer,const Vector3f & origin, const float & fov, const float &ratio, const unsigned int & offset) const;

    ///\brief Enregistre la scène dans un fichier
    void saveToFile(const Vector3f * frameBuffer,const int &offset=0);

    /// @brief Affichage en temps réel sur la fenetre QT
    /// @param singleFrame true : permet de charger 1 seule fois l'image si le rendu n'est pas actif
    void permSave(bool singleFrame);

private:

    int imagecount=0;
    Vector3f * frameBuffer;
    Vector3f * depthBuffer;
    Vector3f * GIBuffer;
    Vector3f * photonBuffer;

};

/// @brief Convertion degrés vers rad
/// @param deg valeur a convertir en radian
float deg2rad(const float &deg);


#endif //RAYTRACING_RENDERER_H
