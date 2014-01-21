#include "game.h"

#include "etc/windowmanager.h"

#include "sound/soundmanager.h"
#include "gamescenario.h"


Game::Game():
    m_inputHandler(&m_player),
    m_viewer(Viewport(0, 0, WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height())),
    m_gameScene(this),
    m_hmdManager(this),
    m_soundManager(new SoundManager())
{
    m_viewer.setScene(&m_gameScene);
    m_viewer.setCameraHead(&m_player.cameraDolly().cameraHead());
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

SoundManager& Game::soundManager() {
    return *m_soundManager;
}

void Game::initialize() {
    GameScenario scenario;
    scenario.populate(this);
}

void Game::update(float deltaSec) {
    if (deltaSec == 0.0f) {
        return;
    }

    deltaSec = glm::min(1.0f, deltaSec);

    World::instance()->update(deltaSec);
    m_player.update(deltaSec);
    m_inputHandler.update(deltaSec);
    m_soundManager->setListener(m_player.playerShip()->transform().position(), m_player.playerShip()->transform().orientation());
}

void Game::draw() {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_viewer.draw();
}
