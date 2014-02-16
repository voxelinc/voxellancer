#include "game.h"

#include "etc/contextprovider.h"

#include "sound/soundmanager.h"
#include "world/world.h"
#include "player.h"
#include "camera/cameradolly.h"


class Ship;

Game::Game():
    m_player(this),
    m_inputHandler(&m_player),
    m_viewer(Viewport(0, 0, ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height())),
    m_gameScene(this, &m_player),
    m_hmdManager(this),
    m_scenario(this, "data/scripts/scenarios/minimal.lua")
{
    m_scenario.load();

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

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.03f, deltaSec);

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

void Game::setOutputBuffer(int i) {
    m_gameScene.setOutputBuffer(i);
}

