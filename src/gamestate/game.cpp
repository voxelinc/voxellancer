#include "game.h"

#include <GL/glew.h>

#include "etc/contextprovider.h"

#include "gamestate/gameplay/gameplay.h"


Game::Game():
    GameState("Game", nullptr),
    m_hmdManager(HMDManager::instance()),
    m_viewer(Viewport(0, 0, ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height())),
    m_gamePlay(new GamePlay(this))
{
    setInitialSubstate(m_gamePlay);
}

GamePlay& Game::gamePlay() {
    return *m_gamePlay;
}

const Scene& Game::scene() const {
    assert(currentSubstate());
    return currentSubstate()->scene();
}

const CameraHead& Game::cameraHead() const {
    assert(currentSubstate());
    return currentSubstate()->cameraHead();
}

HMDManager& Game::hmdManager() {
    return *m_hmdManager;
}

Viewer& Game::viewer() {
    return m_viewer;
}

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.03f, deltaSec);

    GameState::update(deltaSec);

    m_viewer.update(deltaSec);
}

void Game::draw() {
    m_viewer.draw(scene(), cameraHead());
}

