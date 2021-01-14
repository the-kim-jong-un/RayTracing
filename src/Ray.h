//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include "Vector.h"
#include "Object.h"
class Object;

/// @brief Classe des rayons
class Ray {
public:
    Position origin;
    Vector3f direction;
    Ray();
    /// @brief Constructeur de Ray
    /// @param position origine du rayon
    /// @param direction direction du rayon
    Ray(const Position & position, const Vector3f & direction);
};

/// @brief fonction de tracing
/// @param ray Rayon à tracer
/// @param depth maximum de profondeur du rayon
/// @param buffer de profondeur
/// @return la couleur sur pixel
Vector3f sphereTrace(const Ray &ray, const unsigned int &depth, Vector3f &dBuffer, Vector3f &pBuffer);

/// @brief coloration par nombre de pas pour sphereTrace
/// @param steps nombre de pas
/// @return la couleur
Vector3f stepColoring(const unsigned int& steps);

bool traceRay(const Ray &ray, float &inter, Object *& hitObj);
Vector3f castRay(const Ray& ray);
Vector3f shade(const Ray &ray, const float &t, Object *interObject, const unsigned int &depth, Vector3f &pBuffer);

/// @brief Calcul la direction du vecteur de reflection
/// @param I Direction initiale
/// @param N Normale
Vector3f reflect(const Vector3f &I, const Vector3f &N);

/// @brief Calcul la direction du vecteur de refraction
/// @param I Direction initiale
/// @param N Normale
/// @param ior Indice de refraction (indice of refraction)
Vector3f refract(const Vector3f &I, const Vector3f &N, const float & ior);

/// @brief Calcul du fresnel par rapport à la normale
/// @param I Direction initiale
/// @param N Normale
/// @param kr
void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr);

/// @brief sphereTrace simplifié pour le calcul de l'ombre
/// @param ray Rayon a calculer
/// @param maxDist Distance maximum à parcourir pour le ray
bool sphereTraceShadow(const Ray &ray,const float &maxDist);

/// @brief Génère des directions dans une demi-sphère
/// @param r1 Nombre aleatoire 1
/// @param r2 Nombre aleatoire 2
Vector3f uniformSampleHemisphere(const float &r1, const float &r2);

/// @brief Créer un systeme de coordonées relatif a la normale N
/// @param N Normale
/// @param Nt vecteur perpendiculaire a la normale N
/// @param Nb vecteur perpendiculaire a la normale N et au vecteur Nt
void createCoordinateSystem(const Vector3f &N, Vector3f &Nt, Vector3f &Nb);


#endif //RAYTRACING_RAY_H
