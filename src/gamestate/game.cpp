#include "game.h"

#include <GL/glew.h>

#include "etc/contextprovider.h"
#include "etc/hmd/hmdmanager.h"
#include "display/viewer.h"
#include "gamestate/gameplay/gameplay.h"


Game::Game():
    GameState("Game", nullptr),
    m_hmdManager(HMDManager::instance()),
    m_viewer(new Viewer(Viewport(0, 0, ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()))),
    m_gamePlay(new GamePlay(this))
{
    setInitialSubState(m_gamePlay);
}

Game::~Game() = default;

GamePlay& Game::gamePlay() {
    return *m_gamePlay;
}

const Scene& Game::scene() const {
    assert(currentSubState());
    return currentSubState()->scene();
}

const CameraHead& Game::cameraHead() const {
    assert(currentSubState());
    return currentSubState()->cameraHead();
}

HMDManager& Game::hmdManager() {
    return *m_hmdManager;
}

Viewer& Game::viewer() {
    return *m_viewer;
}

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.03f, deltaSec);

    GameState::update(deltaSec);

    m_viewer->update(deltaSec);
}

void Game::draw() {
    m_viewer->draw(scene(), cameraHead());
}

