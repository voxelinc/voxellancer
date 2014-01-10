#include "cameraeye.h"

#include <glow/Texture.h>

#include "world/world.h"

#include "game.h"

#include "camerahead.h"
#include "cameradolly.h"


CameraEye::CameraEye(CameraHead* cameraHead, int viewportWidth, int viewportHeight, glm::vec3 relativePosition):
    m_cameraHead(cameraHead),
    m_relativePosition(relativePosition)
{
    glow::Texture* texture = new glow::Texture(GL_TEXTURE_2D);

    texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    texture->image2D(0, GL_RGB, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, nullptr, GL_TEXTURE_2D);

    m_fbo.attachTexture2D(GL_DRAW_FRAMEBUFFER, texture);

    m_fbo.unbind();
}

void CameraEye::update(float deltaSec) {

}

void CameraEye::draw() {
    m_fbo.bind();

	m_cameraHead->cameraDolly()->game()->skybox()->draw(&m_camera);

    m_voxelRenderer->prepareDraw(&m_camera);

    for (WorldObject * worldObject : World::instance()->worldObjects()) {
        m_voxelRenderer->draw(worldObject);
    }

    m_voxelRenderer->afterDraw();

    m_fbo.unbind();
}

