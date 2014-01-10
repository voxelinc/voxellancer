#pragma once

#include <glm/glm.hpp>

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>

#include "camera.h"


class CameraHead;

class CameraEye {
public:
    CameraEye(CameraHead* cameraHead, int viewportWidth, int viewportHeight, glm::vec3 relativePosition);

    void update(float deltaSec);
    void draw();


protected:
    CameraHead* m_cameraHead;
    Camera m_camera;
    glm::vec3 m_relativePosition;

    glow::FrameBufferObject m_fbo;
};


