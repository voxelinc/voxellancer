#pragma once

#include "camera/camera.h"

#include "view.h"


class Scene;
class CameraHead;

class MonoView: public View {
public:
    MonoView(const Viewport& viewport);

    virtual void setViewport(const Viewport& viewport) override;

    virtual float fovy() const override;
    virtual float zNear() const override;
    virtual float aspectRatio() const override;

    virtual void draw(Scene* scene, CameraHead* cameraHead) override;


protected:
    Camera m_camera;
};

