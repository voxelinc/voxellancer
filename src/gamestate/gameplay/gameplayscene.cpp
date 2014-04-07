#include "gameplayscene.h"

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "display/rendering/framebuffer.h"
#include "display/rendering/renderpipeline.h"
#include "display/rendering/blitter.h"
#include "display/rendering/buffernames.h"
#include "display/rendering/starfield.h"
#include "display/rendering/worldtreerenderer.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/viewport.h"

#include "sound/soundmanager.h"

#include "ui/hud/hud.h"

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleengine.h"

#include "world/world.h"
#include "worldobject/worldobject.h"

#include "skybox.h"
#include "player.h"


GamePlayScene::GamePlayScene(GamePlay& gamePlay):
    m_gamePlay(gamePlay),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_outputBlitter(new Blitter()),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_starField(std::make_shared<Starfield>()),
    m_worldTreeRendererEnabled(false),
    m_worldTreeRenderer(new WorldTreeRenderer()),
    m_framebuffer(nullptr),
    m_currentOutputBuffer(0),
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
    m_framebuffer->setDrawBuffers({ BufferNames::Color, BufferNames::NormalZ, BufferNames::Emissisiveness });

    drawGame(camera);

    RenderMetaData metadata(camera, side);
    m_renderPipeline->apply(*m_framebuffer, metadata);

    // set viewport to original resolution
    glViewport(destinationViewport.x(), destinationViewport.y(), destinationViewport.width(), destinationViewport.height());

    // transfer rendered image to target framebuffer
    m_outputBlitter->setInputMapping({ { "source", m_currentOutputBuffer } });
    m_outputBlitter->apply(*m_framebuffer, target);
}

void GamePlayScene::update(float deltaSec) {
    m_starField->update(deltaSec, m_gamePlay.cameraHead().position());
}

bool GamePlayScene::worldTreeRendererEnabled() const {
    return m_worldTreeRendererEnabled;
}

void GamePlayScene::setWorldTreeRendererEnabled(bool enabled) {
    m_worldTreeRendererEnabled = enabled;
}

void GamePlayScene::setOutputBuffer(int i) {
    m_currentOutputBuffer = glm::min(i, m_renderPipeline->bufferCount() - 1);
    glow::info("Switched to output-buffer: %;", bufferNames[m_currentOutputBuffer]);
}

void GamePlayScene::drawGame(const Camera& camera) const {
    World::instance()->skybox().draw(camera);

    m_voxelRenderer->program()->setUniform("lightdir", m_defaultLightDir.get());

    m_voxelRenderer->prepareDraw(camera);

    for (WorldObject* worldObject : World::instance()->worldObjects()) {
        VoxelRenderer::instance()->draw(*worldObject);
    }

    World::instance()->player().hud().draw();

    m_voxelRenderer->afterDraw();

    World::instance()->particleEngine().draw(camera);

    if (m_worldTreeRendererEnabled) {
        m_worldTreeRenderer->draw(camera);
    }
}

