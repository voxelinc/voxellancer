#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "eyeside.h"

namespace glow {
    class FrameBufferObject;
}

class Scene;
class Camera;
class CameraHead;
class StereoRenderInfo;
class FrameBuffer;

class StereoViewEye {
public:
    StereoViewEye(const glm::ivec2& viewportResolution, const StereoRenderInfo& stereoRenderInfo, EyeSide side);
    ~StereoViewEye();

    FrameBuffer& fbo();

    const Camera& camera() const;

    void setViewportResolution(const glm::ivec2& viewportResolution);

    void draw(const Scene& scene, const CameraHead& cameraHead);


protected:
    glm::vec3 m_offset;
    EyeSide m_side;

    float m_distortionScale;
    glm::ivec2 m_textureSize;
    std::unique_ptr<Camera> m_camera;
    std::unique_ptr<FrameBuffer> m_fbo;
};

