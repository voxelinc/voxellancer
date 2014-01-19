#include "stereovieweye.h"

#include <iostream>

#include <glow/Texture.h>
#include <glow/RenderBufferObject.h>

#include "camera/camerahead.h"

#include "etc/windowmanager.h"

#include "scene.h"
#include "stereorenderinfo.h"


StereoViewEye::StereoViewEye(const StereoRenderInfo& stereoRenderInfo, EyeSide side):
    m_side(side),
    m_camera(WindowManager::instance()->resolution().width()/2, WindowManager::instance()->resolution().height()),
    m_distortionScale(stereoRenderInfo.distortionScale())
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

void StereoViewEye::resize() {
    setupFBO();
}

void StereoViewEye::setupFBO() {
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->bind();

    m_textureSize.setWidth(static_cast<int>(WindowManager::instance()->resolution().width()/2 * m_distortionScale));
    m_textureSize.setHeight(static_cast<int>(WindowManager::instance()->resolution().height() * m_distortionScale));

    texture->image2D(0, GL_RGB, m_textureSize.width(), m_textureSize.height(), 0, GL_RGB, GL_FLOAT, nullptr);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_fbo.attachTexture2D(GL_COLOR_ATTACHMENT0, texture);

    glow::RenderBufferObject* rbo = new glow::RenderBufferObject();
    rbo->storage(GL_DEPTH_COMPONENT, m_textureSize.width(), m_textureSize.height());

    m_fbo.attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);

    m_fbo.unbind();
}


