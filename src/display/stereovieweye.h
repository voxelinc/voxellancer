#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "camera/camera.h"

#include "geometry/size.h"

namespace glow {
    class FrameBufferObject;
}

class Scene;
class CameraHead;
class StereoRenderInfo;
class FrameBuffer;

class StereoViewEye {
public:
    enum EyeSide {
        Left,
        Right
    };

public:
    StereoViewEye(const Size<int>& viewportResolution, const StereoRenderInfo& stereoRenderInfo, EyeSide side);

    glow::FrameBufferObject& fbo();

    void setViewportResolution(const Size<int>& viewportResolution);

    void draw(Scene* scene, CameraHead* cameraHead);


protected:
    glm::vec3 m_offset;
    EyeSide m_side;

    Camera m_camera;

    float m_distortionScale;
    Size<int> m_textureSize;
    std::shared_ptr<FrameBuffer> m_fbo;
};

