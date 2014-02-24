#include "gamescene.h"

#include "voxel/voxelrenderer.h"
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
#include "camera/camera.h"
#include "rendering/starfield.h"
#include "camera/camerahead.h"
#include "voxeleffect/voxelparticleengine.h"


GameScene::GameScene(Game& game, Player& player) :
    m_game(&game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_soundManager(new SoundManager()),
    m_outputBlitter(new Blitter()),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_starField(std::make_shared<Starfield>()),
    m_framebuffer(new FrameBuffer(m_renderPipeline->bufferCount())),
    m_currentOutputBuffer(0),
    m_player(&player),
    m_defaultLightDir("vfx.lightdir")
{
    m_renderPipeline->add(m_starField, 0);
}

GameScene::~GameScene() = default;

void GameScene::draw(Camera& camera, glow::FrameBufferObject* target, EyeSide side) {

    m_framebuffer->setResolution(camera.viewport());
    m_framebuffer->clear();

    drawGame(camera);

    RenderMetaData metadata(&camera, side);
    m_renderPipeline->apply(*m_framebuffer, metadata);

    // transfer rendered image to target framebuffer
    m_outputBlitter->setInputMapping({ { "source", m_currentOutputBuffer } });
    m_outputBlitter->apply(*m_framebuffer, target);
}

void GameScene::activate() {
    m_soundManager->activate();
}

void GameScene::deactivate() {
    m_soundManager->deactivate();
}

void GameScene::update(float deltaSec) {
    m_starField->update(deltaSec, m_player->cameraHead().position());
    m_soundManager->setListener(m_player->cameraHead().position(), m_player->cameraHead().orientation());
}

void GameScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = glm::min(i, m_renderPipeline->bufferCount() - 1);
}

void GameScene::drawGame(Camera& camera) {
    m_framebuffer->setDrawBuffers({ BufferNames::Color, BufferNames::NormalZ, BufferNames::Emissisiveness });

    World::instance()->skybox().draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", m_defaultLightDir.get());
    m_voxelRenderer->prepareDraw(camera);
    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(*worldObject);
    }
    m_game->player().hud().draw();
    m_voxelRenderer->afterDraw();

    World::instance()->particleEngine().draw(camera);

}

