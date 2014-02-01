#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "camera/camera.h"
#include "eyeside.h"

namespace glow {
    class FrameBufferObject;
}

class Scene;
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

    void draw(Scene* scene, CameraHead* cameraHead);


protected:
    glm::vec3 m_offset;
    EyeSide m_side;

    Camera m_camera;

    float m_distortionScale;
    glm::ivec2 m_textureSize;
    std::unique_ptr<FrameBuffer> m_fbo;
};

