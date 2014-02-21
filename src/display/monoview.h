#pragma once

#include <memory>

#include "view.h"


class Scene;
class Camera;
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
    std::unique_ptr<Camera> m_camera;
};

