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


CameraEye::CameraEye(CameraHead* cameraHead, int viewportWidth, int viewportHeight, glm::vec3 relativePosition):
    m_cameraHead(cameraHead),
    m_camera(viewportWidth, viewportHeight),
    m_relativePosition(relativePosition)
{
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture->image2D(0, GL_RGB, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, nullptr, GL_TEXTURE_2D);

    m_fbo.attachTexture2D(GL_DRAW_FRAMEBUFFER, texture);

    m_fbo.unbind();
}

Camera& CameraEye::camera() {
    return m_camera;
}

void CameraEye::update(float deltaSec) {
    m_camera.setPosition(m_cameraHead->position() + m_cameraHead->orientation() * m_relativePosition);
    m_camera.setOrientation(m_cameraHead->orientation());
}

void CameraEye::draw() {
 //   m_fbo.bind();

	World::instance()->skybox().draw(&m_camera);

    VoxelRenderer::instance()->prepareDraw(&m_camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }

    m_cameraHead->hud()->draw();
    World::instance()->voxelParticleWorld().draw(m_camera);

    VoxelRenderer::instance()->afterDraw();

 //   m_fbo.unbind();
}

