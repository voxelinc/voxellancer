#include "game.h"

#include "etc/windowmanager.h"

#include "gamescenario.h"


<<<<<<< HEAD
#include <glow/AutoTimer.h>
#include <glow/logging.h>
/*
#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>
*/
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

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/flytotask.h"
#include "ai/elevatedtasks/patrolwaypointstask.h"


class Ship;

Game::Game():
    m_inputHandler(&m_player),
    m_viewer(Viewport(0, 0, WindowManager::instance()->resolution().width(), WindowManager::instance()->resolution().height())),
    m_gameScene(this),
    m_hmdManager(this)
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
}

void Game::draw() {
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_DEPTH_BUFFER_BIT);

    m_viewer.draw();
}

