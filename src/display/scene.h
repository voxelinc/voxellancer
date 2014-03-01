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
    virtual void draw(const Camera& camera, glow::FrameBufferObject* destination, EyeSide side = EyeSide::None) const = 0;
    virtual void update(float deltaSec) = 0;
};

