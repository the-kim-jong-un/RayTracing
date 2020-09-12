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
    static std::vector<Object*> objects;
    static std::vector<Light*> lights;
    static void test();
};



#endif //RAYTRACING_SCENEMANAGER_H
