#pragma once

#include "camera/camera.h"


class Scene {
public:
    virtual void draw(Camera* camera) = 0;
};

