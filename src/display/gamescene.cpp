#include "gamescene.h"

#include "collision/collisiondetector.h"

#include "sound/soundmanager.h"

#include "ui/hud.h"

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"

#include "world/world.h"

#include "worldobject/worldobject.h"

#include "game.h"
#include "player.h"
#include "skybox.h"


GameScene::GameScene(Game* game):
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
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

    m_hd3000dummy.drawIfActive();
}

void GameScene::activate() {
    m_soundManager->activate();
}

void GameScene::deactivate() {
    m_soundManager->deactivate();
}

void GameScene::setPlayer(Player* player) {
    m_player = player;
}

void GameScene::update(float deltaSec) {
    m_soundManager->setListener(m_player->cameraPosition(), m_player->cameraOrientation());
}

