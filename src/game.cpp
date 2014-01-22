#include "game.h"

#include <GL/glew.h>

#include <algorithm>
#include <random>
#include <memory>
#include <iostream>
#include <fstream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <glow/AutoTimer.h>
#include <glow/logging.h>

#include "property/propertymanager.h"
#include "resource/clustercache.h"
#include "utils/hd3000dummy.h"
#include "utils/linuxvmdummy.h"
#include "ui/inputhandler.h"
#include "ui/hud.h"

#include "world/world.h"
#include "world/god.h"
#include "skybox.h"
#include "voxeleffect/voxelparticleworld.h"
#include "voxel/voxelrenderer.h"
#include "worldobject/ship.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"


#include "battlescenario.h"


class Ship;

Game::Game(GLFWwindow *window) :
    m_window(window),
    m_camera(),
    m_player(&m_camera)
{
}

Game::~Game() {
}

void Game::reloadConfig() {
    PropertyManager::instance()->load("data/config.ini");
}

void Game::initialize() {
    m_world = World::instance();
    //Must be created first
    m_linuxvmdummy = std::unique_ptr<LinuxVMDummy>(new LinuxVMDummy);

    BattleScenario scenario = BattleScenario();
    scenario.loadScenario(this);


    glow::debug("Create Skybox");
    m_skybox = std::unique_ptr<Skybox>(new Skybox);

    m_voxelRenderer = VoxelRenderer::instance();

    glow::debug("Setup Camera");
    //viewport set in resize
    //m_camera.setPosition(glm::vec3(0, 5, 30));
    m_camera.setZNear(1);
    m_camera.setZFar(9999);

    glow::debug("Create HUD");
    m_hud = std::unique_ptr<HUD>(new HUD(&m_player));
    m_hud->setCamera(&m_camera);

    glow::debug("Create InputHandler");
    m_inputHandler = std::unique_ptr<InputHandler>(new InputHandler(m_window, &m_player, &m_camera, m_hud.get()));

    glow::debug("Create Utils");
    m_hd3000dummy = std::unique_ptr<HD3000Dummy>(new HD3000Dummy);

    m_out = new StreamRedirect(std::cout, m_hud.get(), true);
    m_err = new StreamRedirect(std::cerr, m_hud.get(), true);

	glow::debug("Game::initialize Done");
}


void Game::update(float deltaSec) {
    // skip non-updates
    if (deltaSec == 0) return;

    if (deltaSec < 1 / 60) deltaSec = 1 / 60;
    // avoid big jumps for sudden framerate drops
    deltaSec = glm::min(0.1f, deltaSec);

    m_inputHandler->update(deltaSec);
    m_player.applyUpdate();
    World::instance()->update(deltaSec);
    m_player.setFollowCam();
    m_hud->update(deltaSec);
}

void Game::draw() {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_skybox->draw(&m_camera);

    m_voxelRenderer->prepareDraw(&m_camera);
    for (WorldObject * worldObject : m_world->worldObjects()) {
        m_voxelRenderer->draw(worldObject);
    }

    // draw all other voxelclusters...
    m_voxelRenderer->afterDraw();

    World::instance()->voxelParticleWorld().draw(m_camera);

    m_hud->draw();

    m_hd3000dummy->drawIfActive();
}

InputHandler* Game::inputHandler() {
    return m_inputHandler.get();
}

Player& Game::player() {
    return m_player;
}