//
// Created by constantin on 11/09/2020.
//
#include "Vector.h"
#include "SceneManager.h"
#include "random"
#include "ComplexObject.h"
#include "ComplexObjectSubstract.h"
#include "ComplexObjectIntersect.h"
#include "ComplexObjectUnion.h"
#include "Object.h"
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "Plane.h"
#include "Camera.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);


void SceneManager::clear() {
    int oDeleted = 0;
    std::cout << "Clear Scene" << '\n';
    if (!SceneManager::objects.empty()) {
        for (auto &object : SceneManager::objects) {
            delete object;
            oDeleted++;
        }
        objects.clear();
    }
    if (!SceneManager::lights.empty()) {
        for (auto &object : SceneManager::lights) {
            delete object;
            oDeleted++;
        }
        lights.clear();
    }
    std::cout << "Scene cleared, " << oDeleted << " objects deleted" << '\n';
}

SceneManager::SceneManager() {
    Vector3f lookAtVec = Vector3f(-20, 10, 10);
    Camera::cameraToWorld = Camera::lookAt(lookAtVec, Vector3f());
    self = this;
}

void SceneManager::addObject(Object *ob) {
    SceneManager::objects.push_back(ob);
}

void SceneManager::addLight(PointLight *ob) {
    SceneManager::lights.push_back(ob);
}

void SceneManager::loadPremadeScene(const unsigned int &sceneN) {
    if (!bIsLoading) {
        bIsLoading = true;
        clear();
        std::cout << "Loading base scene" << '\n';
        auto *pl = new Plane(Vector3f(0, 1, 0), Vector3f(0, -2, 0));
        pl->mat.albedo = Vector3f(0.5, 0.5, 0.5);
        pl->mat.matReflection = 0.f;
        auto *wall1 = new Plane(Vector3f(0, 0, 1), Vector3f(0, 0, -25));
        auto *wall2 = new Plane(Vector3f(0, -1, 0), Vector3f(0, 23, 0));
        auto *wall3 = new Plane(Vector3f(-1, 0, 0), Vector3f(25, 0, 0));
        wall1->mat = Material(Vector3f(0, 0.5f, 0), 0.8, 0.08, 0.f, 4);
        wall2->mat = Material(Vector3f(0, 0, 0.5f), 0.8, 0.08, 0, 4);
        wall3->mat = Material(Vector3f(0.5f, 0, 0), 0.8, 0.08, 1.f, 4);
        SceneManager::addObject(pl);
        SceneManager::addObject(wall1);
        SceneManager::addObject(wall2);
        SceneManager::addObject(wall3);
        std::cout << "Loading scene : " << sceneN << '\n';
        switch (sceneN) {
            case 0: {
                auto *orig = new Cube(Vector3f(4, 4, 4));
                orig->rotation = Vector3f(0, 0, 0);
                orig->position = Vector3f(0, 0, 0);
                orig->mat = Material(Albedo(0.1, 0.1, 0.8), 0.4, 0.02);
                orig->mat.matReflection = 1.0f;
                orig->mat.matRefraction = 1.2f;
                auto *sphOrig = new Sphere(Vector3f(0, 0, 0), 4.6f, Material(Albedo(0.6)));
                auto *midSph = new Sphere(Vector3f(0, 0, 0), 1.5f,
                                          Material(Albedo(1.f, 0.f, 1.f), 0.8, 0.08, 1.f, 4, 1.5f));
                auto *cornerCube = new Cube(Vector3f(2.5, 2.5, 2.5));
                cornerCube->position = Vector3f(-3.f, 3.f, 3.f);
                cornerCube->rotation = Vector3f(0, 45, 45);
                auto *cpl = new ComplexObjectSubstract(orig, sphOrig);
                auto *outSph = new Sphere(Vector3f(), 5.f, Material());
                auto *gud = new ComplexObjectIntersect(outSph, cpl);
                auto *final = new ComplexObjectSubstract(gud, cornerCube);
                final->mat = Material(Albedo(0.9, 0.3, 0.6), 0.4, 0.02, 0.6f, 4, 0.f);
                SceneManager::addObject(final);
                SceneManager::addObject(midSph);
                auto *testLight = new PointLight(Vector3f(-15, 45, 15.6) * 0.5f, Vector3f(15, 10, 10), 550);
                SceneManager::addLight(testLight);
                break;
            }
            case 1: {
                float spawnSpread = 12;
                int numSpheres = 64;
                gen.seed(time(NULL));
                for (uint32_t i = 0; i < numSpheres; ++i) {
                    Vector3f randPos((0.5 - dis(gen)) * spawnSpread, (0.5 - dis(gen)) * spawnSpread,
                                     (0.5 - dis(gen)) * spawnSpread);
                    float randRadius = 0.7f + (float) dis(gen) * 0.7f;
                    Material tmpMat(Vector3f(dis(gen)/5, dis(gen) / 5, dis(gen) / 5),0.8, 0.08, dis(gen), 4, dis(gen) > 0.62 ? 1.2 + dis(gen) * 0.5 : 0.f);
                    SceneManager::objects.push_back(new Sphere(randPos, randRadius, tmpMat));
                }


                auto *testLight = new PointLight(Vector3f(-15, 45, 15.6) * 0.5f, Vector3f(15, 10, 10), 550);
                SceneManager::addLight(testLight);
                break;
            }
            case 2: {
                auto *testLight = new PointLight(Vector3f(-15, 45, 15.6) * 0.5f, Vector3f(15, 10, 10), 550);
                SceneManager::addLight(testLight);

                auto *midSph = new Sphere(Vector3f(0, 1.5, 0), 2.5f,
                                          Material(Albedo(1.f, 1.f, 1.f), 0.8, 0.08, 1.f, 4, 1.5f));
                auto *backSph = new Sphere(Vector3f(7, 0, -7), 1.5f, Material(Albedo(0.8f, 0, 0)));


                addObject(midSph);
                addObject(backSph);
                break;
            }
            default:
                break;
        }
        std::cout << "Scene loaded, objects in scene : " << objects.size() << '\n';
        bIsLoading = false;
    }
}
