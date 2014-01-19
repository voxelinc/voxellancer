#pragma once

#include "geometry/viewport.h"


class CameraHead;
class Scene;

class View {
public:
    View(const Viewport& viewport);
    virtual ~View();

    virtual void setViewport(const Viewport& viewport);

    virtual void draw(Scene* scene, CameraHead* cameraHead) = 0;


protected:
    Viewport m_viewport;
};

