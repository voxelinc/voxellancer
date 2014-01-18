#include "cameraeye.h"

#include <iostream>

#include <glow/Texture.h>

#include "voxeleffect/voxelparticleworld.h"

#include "world/world.h"

#include "game.h"
#include "skybox.h"

#include "camerahead.h"
#include "cameradolly.h"


CameraEye::CameraEye(CameraHead* cameraHead, const Viewport& viewport, glm::vec3 relativePosition, float renderResolutionFactor):
    m_voxelRenderer(VoxelRenderer::instance()),
    m_cameraHead(cameraHead),
    m_camera(viewport.width(), viewport.height()),
    m_relativePosition(relativePosition),
    m_viewport(viewport)
{
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->bind();

    m_textureSize.setWidth(m_viewport.width() * renderResolutionFactor);
    m_textureSize.setHeight(m_viewport.height() * renderResolutionFactor);
    texture->image2D(0, GL_RGB, m_textureSize.width(), m_textureSize.height(), 0, GL_RGB, GL_FLOAT, nullptr);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    m_fbo.attachTexture2D(GL_COLOR_ATTACHMENT0, texture);

    glow::RenderBufferObject* rbo = new glow::RenderBufferObject();
    rbo->storage(GL_DEPTH_COMPONENT, m_textureSize.width(), m_textureSize.height());

    m_fbo.attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);

    m_fbo.unbind();
}

Camera& CameraEye::camera() {
    return m_camera;
}

glow::FrameBufferObject& CameraEye::fbo() {
    return m_fbo;
}

Viewport& CameraEye::viewport() {
    return m_viewport;
}

void CameraEye::update(float deltaSec) {
    m_camera.setPosition(m_cameraHead->position() + m_cameraHead->orientation() * m_relativePosition);
    m_camera.setOrientation(m_cameraHead->orientation());
}

void CameraEye::draw() {
    m_fbo.bind();

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_textureSize.width(), m_textureSize.height());

	World::instance()->skybox().draw(&m_camera);

    m_voxelRenderer->prepareDraw(&m_camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }

    m_cameraHead->hud()->draw();
    World::instance()->voxelParticleWorld().draw(m_camera);

    m_voxelRenderer->afterDraw();

    m_hd3000dummy.drawIfActive();

    m_fbo.unbind();
}



