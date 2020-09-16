//
// Created by constantin on 11/09/2020.
//

#include "SceneManager.h"

void SceneManager::clear() {
    for (auto & object : SceneManager::objects){
        delete object;
    }
    SceneManager::objects.empty();
}
