#pragma once

#include "camera/camera.h"


class Scene {
public:
    Scene();

    virtual void draw(Camera* camera) = 0;
};

