#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Ray.h"
#include "SceneManager.h"

int main() {
    unsigned int sizeX=1000;
    unsigned int sizeY=1000;
    Vector3f test(1,2,3);
    Vector3f add(5,0,2);
    test = normalize(test) + add;
    test.print();
    float T = INFINITY;
    return 0;
}
