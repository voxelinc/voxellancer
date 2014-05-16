#include "gameplayscene.h"

#include <glow/logging.h>
#include <glow/Program.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "display/rendering/starfield.h"
#include "display/rendering/skybox.h"
#include "display/rendering/worldtreerenderer.h"

#include "gamestate/gameplay/gameplay.h"

#include "geometry/viewport.h"

#include "sound/soundmanager.h"

#include "ui/hud/hud.h"

#include "voxeleffect/voxelparticleengine.h"

#include "worldobject/worldobject.h"

#include "player.h"


GamePlayScene::GamePlayScene(GamePlay& gamePlay):
    m_gamePlay(gamePlay),
    m_starField(std::make_shared<Starfield>()),
    m_worldTreeRendererEnabled(false),
    m_worldTreeRenderer(new WorldTreeRenderer())
{
    addRenderPass(m_starField, 0);
}

GamePlayScene::~GamePlayScene() = default;

void GamePlayScene::update(float deltaSec) {
    m_starField->update(deltaSec, m_gamePlay.cameraHead().position());
}

bool GamePlayScene::worldTreeRendererEnabled() const {
    return m_worldTreeRendererEnabled;
}

void GamePlayScene::setWorldTreeRendererEnabled(bool enabled) {
    m_worldTreeRendererEnabled = enabled;
}

void GamePlayScene::drawImpl(const Camera& camera) const {
    Sector* sector = m_gamePlay.universe()->player().sector();

    if (sector) {
        sector->draw(camera);

        if (m_worldTreeRendererEnabled) {
            m_worldTreeRenderer->draw(camera, sector->worldTree());
        }
    }

    m_gamePlay.universe()->player().hud().draw();
}

