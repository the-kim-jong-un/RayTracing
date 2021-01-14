//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_SCENEMANAGER_H
#define RAYTRACING_SCENEMANAGER_H



#include <vector>
#include "Object.h"
#include "Light.h"


/// @brief Classe gerant la scène a rendre lors du rendu de Renderer
class SceneManager {
public:

    static SceneManager * self;
    static bool bIsLoading;

    static std::vector<Object*> objects;
    static std::vector<PointLight*> lights;

    SceneManager();

    /// @brief Ajoute un object pour le rendu de la scène
    /// @param ob Object à ajouter
    static void addObject(Object * ob);

    /// @brief Ajoute une source de lumière pour le rendu de la scène
    /// @param ob source à ajouter
    static void addLight(PointLight *ob);

    /// @brief Vide la scène
    static void clear();

    /// @brief Charge une scène prédefinie
    /// @param sceneN Choix de la scène
    static void loadPremadeScene(const unsigned int &sceneN );

private:

};



#endif //RAYTRACING_SCENEMANAGER_H
