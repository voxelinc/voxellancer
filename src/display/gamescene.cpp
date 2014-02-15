#include "gamescene.h"

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleengine.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"
#include "game.h"
#include "rendering/framebuffer.h"
#include "rendering/renderpipeline.h"
#include "rendering/blitter.h"
#include "player.h"
#include "ui/hud/hud.h"
#include "world/world.h"
#include "skybox.h"
#include "worldobject/worldobject.h"
#include "rendering/buffernames.h"


GameScene::GameScene(Game* game, Player* player) :
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager()),
    m_blitter(new Blitter()),
    m_renderPipeline(RenderPipeline::getDefault(player)),
    m_framebuffer(new FrameBuffer(m_renderPipeline->bufferCount())),
    m_currentOutputBuffer(0),
    m_player(player),
    m_defaultLightDir("vfx.lightdir")
{

}

GameScene::~GameScene() = default;

void GameScene::draw(Camera* camera, glow::FrameBufferObject* target, EyeSide side) {

    m_framebuffer->setResolution(camera->viewport());
    m_framebuffer->clear();

    // the pipeline should expect color in 1, normals in 2 and emissiveness in 3
    m_framebuffer->setDrawBuffers({ BufferNames::Color, BufferNames::NormalZ, BufferNames::Emissisiveness });
    drawGame(camera);

    m_renderPipeline->apply(*m_framebuffer, *camera, side);

    m_blitter->setInputMapping({ { "source", m_currentOutputBuffer } });
    m_blitter->apply(*m_framebuffer, target);
}

void GameScene::activate() {
    m_soundManager->activate();
}

void GameScene::deactivate() {
    m_soundManager->deactivate();
}

void GameScene::update(float deltaSec) {
    m_renderPipeline->update(deltaSec);

    CameraHead& cameraHead = m_player->cameraDolly().cameraHead();
    m_soundManager->setListener(cameraHead.position(), cameraHead.orientation());
}

void GameScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = glm::min(i, m_renderPipeline->bufferCount() - 1);
}

void GameScene::drawGame(Camera* camera) {
    World::instance()->skybox().draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", m_defaultLightDir.get());
    m_voxelRenderer->prepareDraw(camera);
    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(worldObject);
    }
    m_game->player().hud().draw();
    m_voxelRenderer->afterDraw();

    World::instance()->voxelParticleEngine().draw(*camera);

    m_hd3000dummy->drawIfActive();
}

