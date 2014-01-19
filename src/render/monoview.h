#pragma once

#include "view.h"

class Scene;
class CameraHead;

class MonoView: public View {
public:
    MonoView();

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;
};

