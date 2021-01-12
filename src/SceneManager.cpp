//
// Created by constantin on 11/09/2020.
//

#include "SceneManager.h"
#include "ComplexObject.h"
#include "ComplexObjectSubstract.h"
#include "ComplexObjectIntersect.h"
#include "ComplexObjectUnion.h"
#include "Object.h"
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "Plane.h"

void SceneManager::clear() {
    std::cout<<"Clear Scene"<<'\n';
    if (!SceneManager::objects.empty()) {
        for (auto &object : SceneManager::objects) {
            delete object;
        }
        objects.clear();
    }
    if (!SceneManager::lights.empty()) {
        for (auto &object : SceneManager::lights) {
            delete object;
        }
        lights.clear();
    }
}

SceneManager::SceneManager() {
    self = this;
}

void SceneManager::addObject(Object *ob) {
    SceneManager::objects.push_back(ob);
}

void SceneManager::addLight(PointLight *ob) {
    SceneManager::lights.push_back(ob);

}

void SceneManager::loadPremadeScene(const unsigned int &sceneN) {
    clear();
    std::cout<<"Loading base scene"<<'\n';
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
    std::cout<<"Loading scene : "<<sceneN<<'\n';
    switch (sceneN) {
        case 0: {
            auto * orig = new Cube(Vector3f(4,4,4));
            orig->rotation=Vector3f(0,0,0);
            orig->position=Vector3f(0,0,0);
            orig->mat= Material(Albedo(0.1,0.1,0.8),0.4,0.02);
            orig->mat.matReflection=1.0f;
            orig->mat.matRefraction=1.2f;
            auto * sphOrig= new Sphere(Vector3f(0,0,0),4.6f,Material(Albedo(0.6)));
            auto * midSph = new Sphere(Vector3f(0,0,0),1.5f,Material(Albedo(1.f,0.f,1.f),0.8,0.08,1.f,4,1.5f));
            auto * cornerCube = new Cube(Vector3f(2.5,2.5,2.5));
            cornerCube->position=Vector3f(-3.f,3.f,3.f);
            cornerCube->rotation=Vector3f(0,45,45);
            auto * cpl = new ComplexObjectSubstract(orig,sphOrig);
            auto * outSph= new Sphere(Vector3f(),5.f,Material());
            auto * gud= new ComplexObjectIntersect(outSph,cpl);
            auto * final= new ComplexObjectSubstract(gud,cornerCube);
            final->mat= Material(Albedo(0.9,0.3,0.6),0.4,0.02,0.6f,4,0.f);
            SceneManager::addObject(final);
            SceneManager::addObject(midSph);
            auto * testLight = new PointLight(Vector3f (-15,45,15.6)*0.5f,Vector3f(15, 10, 10),300);
            SceneManager::addLight(testLight);
            break;
        }
        case 1: {
            auto * testLight = new PointLight(Vector3f (-15,45,15.6)*0.5f,Vector3f(15, 10, 10),300);
            SceneManager::addLight(testLight);
            break;
        }
        case 2: {
            auto * testLight = new PointLight(Vector3f (-15,45,15.6)*0.5f,Vector3f(15, 10, 10),300);
            SceneManager::addLight(testLight);

            auto * midSph = new Sphere(Vector3f(0,1.5,0),2.5f,Material(Albedo(1.f,1.f,1.f),0.8,0.08,1.f,4,1.5f));
            auto * backSph = new Sphere(Vector3f(7,0,-7),1.5f,Material(Albedo(0.8f,0,0)));


            addObject(midSph);
            addObject(backSph);
            break;
        }
        default:
            break;
    }
    std::cout<<"Objects in scene : "<<objects.size()<<'\n';
}
