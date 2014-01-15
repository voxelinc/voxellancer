#include "cameraeye.h"

#include <iostream>

#include <glow/Texture.h>

#include "voxel/voxelrenderer.h"

#include "voxeleffect/voxelparticleworld.h"

#include "world/world.h"

#include "game.h"
#include "skybox.h"

#include "camerahead.h"
#include "cameradolly.h"


CameraEye::CameraEye(CameraHead* cameraHead, const Viewport& viewport, glm::vec3 relativePosition):
    m_cameraHead(cameraHead),
    m_camera(viewport.width(), viewport.height()),
    m_relativePosition(relativePosition),
    m_viewport(viewport)
{
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture->image2D(0, GL_RGB, m_viewport.width(), m_viewport.height(), 0, GL_RGB, GL_FLOAT, nullptr, GL_TEXTURE_2D);

    m_fbo.attachTexture2D(GL_DRAW_FRAMEBUFFER, texture);

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

	World::instance()->skybox().draw(&m_camera);

    VoxelRenderer::instance()->prepareDraw(&m_camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }

    m_cameraHead->hud()->draw();
    World::instance()->voxelParticleWorld().draw(m_camera);

    VoxelRenderer::instance()->afterDraw();

    m_fbo.unbind();
}



