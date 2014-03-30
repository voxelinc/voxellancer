#include "game.h"

#include <GL/glew.h>

#include "etc/contextprovider.h"
#include "etc/hmd/hmdmanager.h"
#include "display/viewer.h"
#include "gamestate/gameplay/gameplay.h"


Game* Game::s_instance(nullptr);

Game::Game():
    GameState("Game", nullptr),
    m_hmdManager(HMDManager::instance()),
    m_viewer(new Viewer(Viewport(0, 0, ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()))),
    m_gamePlay(new GamePlay(this))
{
    setInitialSubState(m_gamePlay);
}

Game::~Game() = default;

Game* Game::instance() {
    if (!s_instance) {
        s_instance = new Game();
    }
    return s_instance;
}

void Game::tearDown() {
    delete s_instance;
    s_instance = nullptr;
}

GamePlay& Game::gamePlay() {
    return *m_gamePlay;
}

const Scene& Game::scene() const {
    assert(currentSubState());
    const GameState* subState = dynamic_cast<const GameState*>(currentSubState());
    return subState->scene();
}

const CameraHead& Game::cameraHead() const {
    assert(currentSubState());
    const GameState* subState = dynamic_cast<const GameState*>(currentSubState());
    return subState->cameraHead();
}

HMDManager& Game::hmdManager() {
    return *m_hmdManager;
}

Viewer& Game::viewer() {
    return *m_viewer;
}

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.05f, deltaSec); // slow down to 20 frames
    deltaSec = glm::max(0.0001f, deltaSec); // avoid div by 0

    GameState::update(deltaSec);

    m_viewer->update(deltaSec);
}

void Game::draw() {
    m_viewer->draw(scene(), cameraHead());
}

