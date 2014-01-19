#pragma once


class View {
public:
    View();
    virtual ~View();

    virtual void draw(Scene* scene, CameraHead* cameraHead) = 0;
};

