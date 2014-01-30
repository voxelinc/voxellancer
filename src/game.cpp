#include "game.h"

#include <GL/glew.h>

#include "etc/windowmanager.h"

#include "sound/soundmanager.h"
#include "gamescenario.h"
#include "world/world.h"
#include "player.h"
#include "camera/cameradolly.h"
#include "ui/hud.h"

class Ship;

Game::Game():
    m_inputHandler(&m_player),
    m_viewer(Viewport(0, 0, WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height())),
    m_gameScene(this),
    m_hmdManager(this)
{
    m_viewer.setScene(&m_gameScene);
    m_viewer.setCameraHead(&m_player.cameraDolly().cameraHead());
    m_gameScene.setPlayer(&m_player);
}

InputHandler& Game::inputHandler() {
    return m_inputHandler;
}

Player& Game::player() {
    return m_player;
}

Viewer& Game::viewer() {
    return m_viewer;
}

HMDManager& Game::hmdManager() {
    return m_hmdManager;
}

void Game::initialize() {
    assert(m_viewer.scene() == &m_gameScene);
    GameScenario scenario;
    scenario.populate(this);
}

void Game::update(float deltaSec) {
    if (deltaSec == 0.0f) {
        return;
    }
    deltaSec = glm::min(1.0f, deltaSec);
    
    m_viewer.update(deltaSec);
    World::instance()->update(deltaSec);
    m_player.update(deltaSec);
    m_inputHandler.update(deltaSec);
}

void Game::draw() {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_viewer.draw();
}
