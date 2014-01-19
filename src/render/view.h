#pragma once

class Scene;
class CameraHead;

class View {
public:
    virtual ~View() {};

    virtual void resized() = 0;

    virtual void draw(Scene* scene, CameraHead* cameraHead) = 0;
};

