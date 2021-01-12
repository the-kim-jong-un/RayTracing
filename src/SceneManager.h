//
// Created by constantin on 11/09/2020.
//

#ifndef RAYTRACING_SCENEMANAGER_H
#define RAYTRACING_SCENEMANAGER_H



#include <vector>
#include "Object.h"
#include "Light.h"
class SceneManager {
public:
    static SceneManager * self;

    static std::vector<Object*> objects;
    static std::vector<PointLight*> lights;

    SceneManager();

    static void addObject(Object * ob);
    static void addLight(PointLight *ob);
    static void clear();
    static void loadPremadeScene(const unsigned int &sceneN );
};



#endif //RAYTRACING_SCENEMANAGER_H
