//
// Created by constantin on 11/09/2020.
//

#include "SceneManager.h"

void SceneManager::clear() {
    for (int index=0; index<SceneManager::objects.size(); index++){
        delete SceneManager::objects[index];
    }
    SceneManager::objects.empty();
}
