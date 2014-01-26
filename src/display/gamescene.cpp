#include "gamescene.h"

#include <glow/FrameBufferObject.h>

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"
#include "screenblitter.h"
#include "game.h"
#include "geometry/size.h"
#include "framebuffer.h"


GameScene::GameScene(Game* game):
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager()),
    m_blitter(new ScreenBlitter()),
    m_colorFbo(new FrameBuffer())
{
}

void GameScene::draw(Camera* camera, glow::FrameBufferObject* destination) {
    destination->bind();

    World::instance()->skybox().draw(camera);

    m_voxelRenderer->prepareDraw(camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }

    m_game->player().hud().draw();

    m_voxelRenderer->afterDraw();

    World::instance()->voxelParticleWorld().draw(*camera);

    m_hd3000dummy->drawIfActive();

    destination->unbind();
}

void GameScene::activate() {
    m_soundManager->activate();
}

void GameScene::deactivate() {
    m_soundManager->deactivate();
}

void GameScene::setCameraHead(CameraHead* head) {
    m_head = head;
}

void GameScene::update(float deltaSec) {
    m_soundManager->setListener(m_head->position(), m_head->orientation());
}

void GameScene::setViewportResolution(const Size<int>& viewportResolution) {
    m_colorFbo->setResolution(viewportResolution);
}