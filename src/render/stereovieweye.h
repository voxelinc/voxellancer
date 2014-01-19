#pragma once

#include <glm/glm.hpp>

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>

#include "camera/camera.h"

#include "geometry/size.h"



class Scene;
class CameraHead;
class StereoRenderInfo;

class StereoViewEye {
public:
    enum EyeSide {
        Left,
        Right
    };

public:
    StereoViewEye(const StereoRenderInfo& stereoRenderInfo, EyeSide side);

    glow::FrameBufferObject& fbo();

    void resize();

    void draw(Scene* scene, CameraHead* cameraHead);


protected:
    glm::vec3 m_offset;
    EyeSide m_side;

    Camera m_camera;

    float m_distortionScale;
    Size<int> m_textureSize;
    glow::FrameBufferObject m_fbo;


    void setupFBO();
};

