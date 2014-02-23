#include "game.h"

#include <GL/glew.h>

#include <glm/glm.hpp>


#include "display/viewer.h"
#include "display/gamescene.h"

#include "scenarios/gamescenario.h"
#include "scenarios/battlescenario.h"

#include "etc/contextprovider.h"
#include "etc/hmd/hmdmanager.h"

#include "player.h"
#include "world/world.h"

#include "ui/inputhandler.h"
#include "sound/soundmanager.h"


class Ship;

Game::Game():
    m_player(new Player(this)),
    m_inputHandler(new InputHandler(*m_player)),
    m_viewer(new Viewer(Viewport(0, 0, ContextProvider::instance()->resolution().width(), ContextProvider::instance()->resolution().height()))),
    m_gameScene(new GameScene(*this, *m_player)),
    m_hmdManager(new HMDManager(this)),
    m_scenario(new GameScenario(this))
{
    m_scenario->load();

    m_viewer->setScene(*m_gameScene);
    m_viewer->setCameraHead(m_player->cameraHead());
}

Game::~Game() = default;

InputHandler& Game::inputHandler() {
    return *m_inputHandler;
}

Player& Game::player() {
    return *m_player;
}

Viewer& Game::viewer() {
    return *m_viewer;
}

HMDManager& Game::hmdManager() {
    return *m_hmdManager;
}

void Game::update(float deltaSec) {
    deltaSec = glm::min(0.03f, deltaSec);

    m_viewer->update(deltaSec);
    World::instance()->update(deltaSec);
    m_player->update(deltaSec);
    m_inputHandler->update(deltaSec);
}

void Game::draw() {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_viewer->draw();
}

void Game::setOutputBuffer(int i) {
    m_gameScene->setOutputBuffer(i);
}

