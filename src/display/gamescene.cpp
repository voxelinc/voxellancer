#include "gamescene.h"

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"

#include "game.h"


GameScene::GameScene(Game* game):
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager())
{
}

void GameScene::draw(Camera* camera) {
    World::instance()->skybox().draw(camera);

    m_voxelRenderer->prepareDraw(camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }

    m_game->player().hud().draw();

    m_voxelRenderer->afterDraw();

    World::instance()->voxelParticleWorld().draw(*camera);

    m_hd3000dummy->drawIfActive();
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
