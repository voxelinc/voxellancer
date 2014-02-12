#pragma once

#include <glm/glm.hpp>

#include "display/eyeside.h"

namespace glow {
    class FrameBufferObject;
}

class Camera;
class Viewport;

class Scene {
public:
    virtual void draw(Camera& camera, glow::FrameBufferObject* destination, EyeSide side = EyeSide::Left) = 0;
    virtual void update(float deltaSec) = 0;

    // is called by the viewer
    virtual void activate() = 0;
    virtual void deactivate() = 0;
};

