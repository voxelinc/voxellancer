#include "game.h"

#include <GL/glew.h>

#include "etc/windowmanager.h"

#include "ingame.h"


Game::Game():
    GameState("Game", nullptr),
    m_hmdManager(this),
    m_viewer(Viewport(0, 0, WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height())),
    m_inGame(new InGame(this))
{
    setInitialSubstate(m_inGame);
}

HMDManager& Game::hmdManager() {
    return m_hmdManager;
}

Viewer& Game::viewer() {
    return m_viewer;
}

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.1f, deltaSec);

    GameState::update(deltaSec);

    m_viewer.update(deltaSec);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_viewer.draw();
}

