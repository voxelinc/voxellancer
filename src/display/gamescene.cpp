#include "gamescene.h"

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"
#include "game.h"
#include "rendering/framebuffer.h"
#include "rendering/renderpipeline.h"
#include "rendering/blitter.h"
#include "player.h"
#include "ui/hud.h"
#include "world/world.h"
#include "skybox.h"
#include "worldobject/worldobject.h"


GameScene::GameScene(Game* game):
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager()),
    m_blitter(new Blitter()),
    m_framebuffer(new FrameBuffer(8)),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_currentOutputBuffer(0)
{
}

GameScene::~GameScene() = default;

void GameScene::draw(Camera* camera, glow::FrameBufferObject* target, const glm::ivec2& resolution) {
    m_framebuffer->setResolution(resolution);
    m_framebuffer->clear();

    m_framebuffer->setDrawBuffers({ BufferName::Color, BufferName::NormalZ, BufferName::Emissisiveness });
    drawGame(camera);

    m_renderPipeline->apply(*m_framebuffer);

    m_blitter->setInputMapping({ { "source", static_cast<BufferName>(m_currentOutputBuffer) } });
    m_blitter->apply(*m_framebuffer, target);
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

void GameScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = i;
}

void GameScene::drawGame(Camera* camera) {
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

