#include "stereovieweye.h"

#include <glow/Texture.h>
#include <glow/RenderBufferObject.h>

#include "camera/camerahead.h"
#include "camera/camera.h"

#include "geometry/viewport.h"

#include "rendering/framebuffer.h"
#include "rendering/antialiasing.h"

#include "scene.h"
#include "stereorenderinfo.h"


StereoViewEye::StereoViewEye(const glm::ivec2& viewportResolution, const StereoRenderInfo& stereoRenderInfo, EyeSide side):
    m_side(side),
    m_camera(new Camera(viewportResolution.x, viewportResolution.y)),
    m_distortionScale(stereoRenderInfo.distortionScale()),
    m_fbo(new FrameBuffer()),
    m_antialiasing("vfx.antialiasing") 
{
    setViewportResolution(viewportResolution);

    m_camera->setFovy(stereoRenderInfo.fovy());

    if(m_side == EyeSide::Left) {
        m_offset = stereoRenderInfo.leftEyeOffset();
        m_camera->setProjectionOffset(stereoRenderInfo.leftEyeProjectionOffset());
    } else {
        m_offset = stereoRenderInfo.rightEyeOffset();
        m_camera->setProjectionOffset(stereoRenderInfo.rightEyeProjectionOffset());
    }
}

const Camera& StereoViewEye::camera() const {
    return *m_camera;
}

StereoViewEye::~StereoViewEye() = default;

FrameBuffer& StereoViewEye::fbo() {
    return *m_fbo;
}



void StereoViewEye::draw(const Scene& scene, const CameraHead& cameraHead) {
    int samplingFactor = 1;
    if (m_antialiasing.get() == Antialiasing::SSAA) {
        samplingFactor = 2;
    }
    int sampleWidth = static_cast<int>(m_textureSize.x * samplingFactor);
    int sampleHeight = static_cast<int>(m_textureSize.y * samplingFactor);

    m_camera->setViewport(glm::ivec2(sampleWidth, sampleHeight));
    m_camera->setPosition(cameraHead.position() + cameraHead.orientation() * m_offset);
    m_camera->setOrientation(cameraHead.orientation());

    m_fbo->bind();
    m_fbo->clear();

    glViewport(0, 0, sampleWidth, sampleHeight);

    scene.draw(*m_camera, &m_fbo->get(), Viewport(0,0, m_textureSize.x, m_textureSize.y), m_side);

    m_fbo->unbind();
}

void StereoViewEye::setViewportResolution(const glm::ivec2& viewportResolution) {
    m_textureSize = glm::vec2(viewportResolution) * m_distortionScale;

    m_camera->setViewport(m_textureSize);

    m_fbo->setResolution(m_textureSize);
}
