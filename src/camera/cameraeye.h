#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <glow/Buffer.h>
#include <glow/FrameBufferObject.h>
#include <glow/RenderBufferObject.h>

#include "geometry/viewport.h"

#include "utils/hd3000dummy.h"

#include "voxel/voxelrenderer.h"

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
    std::shared_ptr<VoxelRenderer> m_voxelRenderer;

    CameraHead* m_cameraHead;
    Camera m_camera;
    glm::vec3 m_relativePosition;
    Viewport m_viewport;

    glow::FrameBufferObject m_fbo;

	HD3000Dummy m_hd3000dummy;
};


