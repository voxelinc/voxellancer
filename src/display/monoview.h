#pragma once

#include <string>
#include <memory>

#include "view.h"
#include "property/property.h"


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

    virtual void draw(const Scene& scene, const CameraHead& cameraHead) override;


protected:
    std::unique_ptr<Camera> m_camera;
    Property<std::string> m_antialiasing;
};

