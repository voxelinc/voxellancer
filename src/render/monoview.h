#pragma once

#include "view.h"

class Scene;
class CameraHead;

class MonoView: public View {
public:
    MonoView(const Viewport& viewport);

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;
};

