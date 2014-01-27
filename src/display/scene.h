#pragma once

#include <glm/glm.hpp>

namespace glow {
    class FrameBufferObject;
}

class Camera;
class Viewport;

class Scene {
public:
    virtual void draw(Camera* camera, glow::FrameBufferObject* destination, const glm::ivec2& resolution) = 0;
    virtual void update(float deltaSec) = 0;
    virtual void setViewport(const glm::ivec2& viewport) = 0;

    // is called by the viewer
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    
};

