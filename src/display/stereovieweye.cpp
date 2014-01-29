#include "stereovieweye.h"

#include <iostream>

#include <glow/Texture.h>
#include <glow/RenderBufferObject.h>

#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "scene.h"
#include "rendering/framebuffer.h"
#include "stereorenderinfo.h"


StereoViewEye::StereoViewEye(const Size<int>& viewportResolution, const StereoRenderInfo& stereoRenderInfo, EyeSide side):
    m_side(side),
    m_camera(viewportResolution.width(), viewportResolution.height()),
    m_distortionScale(stereoRenderInfo.distortionScale()),
    m_fbo(new FrameBuffer())
{
    setViewportResolution(viewportResolution);

    m_camera.setFovy(stereoRenderInfo.fovy());

    if(m_side == Left) {
        m_offset = stereoRenderInfo.leftEyeOffset();
        m_camera.setProjectionOffset(stereoRenderInfo.leftEyeProjectionOffset());
    } else {
        m_offset = stereoRenderInfo.rightEyeOffset();
        m_camera.setProjectionOffset(stereoRenderInfo.rightEyeProjectionOffset());
    }
}


StereoViewEye::~StereoViewEye() = default;

FrameBuffer& StereoViewEye::fbo() {
    return *m_fbo;
}

void StereoViewEye::draw(Scene* scene, CameraHead* cameraHead) {
    m_camera.setPosition(cameraHead->position() + cameraHead->orientation() * m_offset);
    m_camera.setOrientation(cameraHead->orientation());

    m_fbo->bind();
    m_fbo->clear();

    glViewport(0, 0, m_textureSize.width(), m_textureSize.height());

    scene->draw(&m_camera, &m_fbo->get(), glm::ivec2(m_textureSize.width(), m_textureSize.height()));

    m_fbo->unbind();
}

void StereoViewEye::setViewportResolution(const Size<int>& viewportResolution) {
    m_textureSize.setWidth(static_cast<int>(viewportResolution.width() * m_distortionScale));
    m_textureSize.setHeight(static_cast<int>(viewportResolution.height() * m_distortionScale));

    m_camera.setViewport(glm::ivec2(viewportResolution.width(), viewportResolution.height()));

    m_fbo->setResolution(glm::ivec2(m_textureSize.width(), m_textureSize.height()));
}
