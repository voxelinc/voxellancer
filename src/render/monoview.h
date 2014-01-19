#pragma once

#include "view.h"

class Scene;
class CameraHead;

class MonoView: public View {
public:
    MonoView();

    void resized() override;

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;
};

