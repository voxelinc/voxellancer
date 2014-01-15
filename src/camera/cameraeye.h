#pragma once

#include <glm/glm.hpp>

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>

#include "geometry/viewport.h"

#include "camera.h"


class CameraHead;

class CameraEye {
public:
    CameraEye(CameraHead* cameraHead, const Viewport& viewport, glm::vec3 relativePosition);

    Camera& camera();
    glow::FrameBufferObject& fbo();
    Viewport& viewport();

    void update(float deltaSec);
    void draw();


protected:
    CameraHead* m_cameraHead;
    Camera m_camera;
    glm::vec3 m_relativePosition;
    Viewport m_viewport;

    glow::FrameBufferObject m_fbo;
};


