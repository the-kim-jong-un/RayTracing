//
// Created by constantin on 11/09/2020.
//

#include "Object.h"

Object::Object() {
    color=Vector3f(255);
}
Object::~Object() {

}

void Object::debug() {
    position.print();
    color.print();
}
