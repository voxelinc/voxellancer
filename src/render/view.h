#pragma once


class View {
public:
    View();
    virtual ~View();

    virtual void resized() = 0;

    virtual void draw(Scene* scene, CameraHead* cameraHead) = 0;
};

