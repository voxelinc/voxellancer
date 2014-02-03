#include "stereovieweye.h"

#include <iostream>

#include <glow/Texture.h>
#include <glow/RenderBufferObject.h>

#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "scene.h"
#include "stereorenderinfo.h"


StereoViewEye::StereoViewEye(const Size<int>& viewportResolution, const StereoRenderInfo& stereoRenderInfo, EyeSide side):
    m_side(side),
    m_camera(viewportResolution.width(), viewportResolution.height()),
    m_distortionScale(stereoRenderInfo.distortionScale()),
    m_viewportResolution(viewportResolution)
{
    setupFBO();

    m_camera.setFovy(stereoRenderInfo.fovy());

    if(m_side == Left) {
        m_offset = stereoRenderInfo.leftEyeOffset();
        m_camera.setProjectionOffset(stereoRenderInfo.leftEyeProjectionOffset());
    } else {
        m_offset = stereoRenderInfo.rightEyeOffset();
        m_camera.setProjectionOffset(stereoRenderInfo.rightEyeProjectionOffset());
    }
}

const Camera& StereoViewEye::camera() const {
    return m_camera;
}

glow::FrameBufferObject& StereoViewEye::fbo() {
    return m_fbo;
}

void StereoViewEye::draw(Scene* scene, CameraHead* cameraHead) {
    m_camera.setPosition(cameraHead->position() + cameraHead->orientation() * m_offset);
    m_camera.setOrientation(cameraHead->orientation());

    m_fbo.bind();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_textureSize.width(), m_textureSize.height());

    scene->draw(&m_camera);

    m_fbo.unbind();
}

void StereoViewEye::setViewportResolution(const Size<int>& viewportResolution) {
    m_viewportResolution = viewportResolution;

    m_camera.setViewport(glm::ivec2(m_viewportResolution.width(), m_viewportResolution.height()));

    setupFBO();
}

void StereoViewEye::setupFBO() {
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->bind();

    m_textureSize.setWidth(static_cast<int>(m_viewportResolution.width() * m_distortionScale));
    m_textureSize.setHeight(static_cast<int>(m_viewportResolution.height() * m_distortionScale));

    texture->image2D(0, GL_RGB, m_textureSize.width(), m_textureSize.height(), 0, GL_RGB, GL_FLOAT, nullptr);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_fbo.attachTexture2D(GL_COLOR_ATTACHMENT0, texture);

    glow::RenderBufferObject* rbo = new glow::RenderBufferObject();
    rbo->storage(GL_DEPTH_COMPONENT, m_textureSize.width(), m_textureSize.height());

    m_fbo.attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);

    m_fbo.unbind();
}


