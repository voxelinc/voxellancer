#pragma once
#include "geometry/size.h"

namespace glow {
    class FrameBufferObject;
}

class Camera;

class Scene {
public:
    virtual void draw(Camera* camera, glow::FrameBufferObject* destination) = 0;
    virtual void update(float deltaSec) = 0;
    virtual void setViewportResolution(const Size<int>& viewportResolution) = 0;

    // is called by the viewer
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    
};

