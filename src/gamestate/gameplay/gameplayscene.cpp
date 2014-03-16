#include "gameplayscene.h"

#include "camera/camera.h"
#include "camera/camerahead.h"
#include "voxel/voxelrenderer.h"
#include "sound/soundmanager.h"
#include "geometry/viewport.h"
#include "gamestate/gameplay/gameplay.h"
#include "display/rendering/framebuffer.h"
#include "display/rendering/renderpipeline.h"
#include "display/rendering/blitter.h"
#include "display/rendering/buffernames.h"
#include "player.h"
#include "ui/hud/hud.h"
#include "world/world.h"
#include "skybox.h"
#include "voxeleffect/voxelparticleengine.h"
#include "worldobject/worldobject.h"
#include "display/rendering/starfield.h"

GamePlayScene::GamePlayScene(GamePlay& gamePlay, Player& player):
    m_gamePlay(gamePlay),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_outputBlitter(new Blitter()),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_starField(std::make_shared<Starfield>()),
    m_framebuffer(nullptr),
    m_currentOutputBuffer(0),
    m_player(player),
    m_defaultLightDir("vfx.lightdir")
{
    m_renderPipeline->add(m_starField, 0);
}

GamePlayScene::~GamePlayScene() = default;

void GamePlayScene::draw(const Camera& camera, glow::FrameBufferObject* target, const Viewport& destinationViewport, EyeSide side) const {
    if (m_framebuffer == nullptr) {
        m_framebuffer.reset(new FrameBuffer(m_renderPipeline->bufferCount()));
    }

    m_framebuffer->setResolution(camera.viewport());
    m_framebuffer->clear();

    drawGame(camera);

    RenderMetaData metadata(camera, side);
    m_renderPipeline->apply(*m_framebuffer, metadata);


    glViewport(destinationViewport.x(), destinationViewport.y(), destinationViewport.width(), destinationViewport.height());
    // transfer rendered image to target framebuffer
    m_outputBlitter->setInputMapping({ { "source", m_currentOutputBuffer } });
    m_outputBlitter->apply(*m_framebuffer, target);
}

void GamePlayScene::update(float deltaSec) {
    m_starField->update(deltaSec, m_player.cameraHead().position());
}

void GamePlayScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = glm::min(i, m_renderPipeline->bufferCount() - 1);
    glow::info("Outputbuffer: %;", bufferNames[m_currentOutputBuffer]);
}

void GamePlayScene::drawGame(const Camera& camera) const {
    m_framebuffer->setDrawBuffers({ BufferNames::Color, BufferNames::NormalZ, BufferNames::Emissisiveness });

    World::instance()->skybox().draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", m_defaultLightDir.get());
    m_voxelRenderer->prepareDraw(camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(*worldObject);
    }
    //m_gamePlay.player().hud().draw();
    m_voxelRenderer->afterDraw();

    World::instance()->particleEngine().draw(camera);

}

