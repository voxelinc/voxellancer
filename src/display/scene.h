#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "display/eyeside.h"


namespace glow {
    class FrameBufferObject;
}

class Blitter;
class Camera;
class FrameBuffer;
class RenderPipeline;
class RenderPass;
class Viewport;

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual void update(float deltaSec) = 0;

    void draw(const Camera& camera, glow::FrameBufferObject* destination, const Viewport& destinationViewport, EyeSide side) const;

    void setOutputBuffer(int i);


protected:
    std::unique_ptr<Blitter> m_outputBlitter;
    std::unique_ptr<RenderPipeline> m_renderPipeline;
    mutable std::unique_ptr<FrameBuffer> m_framebuffer;
    int m_currentOutputBuffer;


    void addRenderPass(const std::shared_ptr<RenderPass>& renderPass, int pos);

    virtual void drawImpl(const Camera& camera) const = 0;
};


