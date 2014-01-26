#include "gamescene.h"

#include <glow/FrameBufferObject.h>

#include "voxel/voxelrenderer.h"
#include "voxeleffect/voxelparticleworld.h"
#include "utils/hd3000dummy.h"
#include "sound/soundmanager.h"
#include "programs/monoblitprogram.h"
#include "game.h"
#include "geometry/size.h"
#include "framebuffer.h"


GameScene::GameScene(Game* game):
    m_game(game),
    m_voxelRenderer(VoxelRenderer::instance()),
    m_hd3000dummy(new HD3000Dummy()),
    m_soundManager(new SoundManager()),
    m_blitter(new MonoBlitProgram()),
    m_framebuffer(new FrameBuffer(5)),
    m_outputBuffer(0)
{
}

void GameScene::draw(Camera* camera, glow::FrameBufferObject* destination, const Viewport& viewPort) {
    m_framebuffer->clear();

    m_framebuffer->setDrawBuffers({ Color, NormalZ, Emissisiveness });
    drawGame(camera);
    
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    m_blitter->setSource(m_framebuffer->texture(m_outputBuffer));
    m_blitter->setDestination(destination, viewPort);
    m_blitter->blit();
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
    m_framebuffer->setResolution(Size<int>(viewportResolution.width(), viewportResolution.height()));
}

void GameScene::setOutputBuffer(int i) {
    m_outputBuffer = i;
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
