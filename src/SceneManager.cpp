//
// Created by constantin on 11/09/2020.
//

#include "SceneManager.h"
#include "Plane.h"

void SceneManager::clear() {
    for (auto & object : SceneManager::objects){
        delete object;
    }
    SceneManager::objects.empty();
}

SceneManager::SceneManager() {
    auto * pl = new Plane(Vector3f(0, 1, 0), Vector3f(0, -2, 0));
    pl->mat.albedo=Vector3f(0.7,0.7,0.7);
    pl->mat.matReflection=1.f;
    auto * wall1=new Plane(Vector3f(0, 0, 1), Vector3f(0, 0, -25));
    auto * wall2=new Plane(Vector3f(0, -1, 0), Vector3f(0, 25,0));
    auto * wall3=new Plane(Vector3f(-1, 0, 0), Vector3f(25,0,0));
    wall1->mat=Material(Vector3f(0,0.5f,0),0.8,0.08,1.f,4);
    wall2->mat=Material(Vector3f(0,0,0.5f),0.8,0.08,0,4);
    wall3->mat=Material(Vector3f(0.5f,0,0),0.8,0.08,1.f,4);
    SceneManager::addObject(pl);
    SceneManager::addObject(wall1);
    SceneManager::addObject(wall2);
    SceneManager::addObject(wall3);
}

void SceneManager::addObject(Object *ob) {
    SceneManager::objects.push_back(ob);
}

void SceneManager::addLight(PointLight *ob) {
    SceneManager::lights.push_back(ob);

}
