#include "game.h"

#include <GL/glew.h>

#include <chrono>
#include <thread>
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


class Ship;

Game::Game(GLFWwindow *window) :
    m_window(window),
    m_inputHandler(window, &m_player)
{
    reloadConfig();
}

Game::~Game() {
}

void Game::reloadConfig() {
    PropertyManager::instance()->load("data/config.ini");
}

void Game::initialize() {
    glow::AutoTimer t("Initialize Game");

    glow::debug("Game::testFMOD()");
    //testFMOD();

    //Must be created first
    m_linuxvmdummy = std::unique_ptr<LinuxVMDummy>(new LinuxVMDummy);

    glow::debug("create world");
    m_world = World::instance();

    m_voxelRenderer = VoxelRenderer::instance();


    glow::debug("Create WorldObjects");
    Ship *normandy = new Ship();
    ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
    normandy->setPosition(glm::vec3(0, 0, -100));
    normandy->objectInfo().setName("Normandy");
    normandy->objectInfo().setShowOnHud(true);
    normandy->objectInfo().setCanLockOn(true);
    m_world->god().scheduleSpawn(normandy);
    // TODO: use these dummies to test BasicTasks
    normandy->setCharacter(
        new DummyCharacter(*normandy,
        new DummyElevatedTask(*normandy,
        new BasicTask(*normandy))));

    Ship *testCluster = new Ship();
    ClusterCache::instance()->fillObject(testCluster, "data/voxelcluster/basicship.csv");
    testCluster->setPosition(glm::vec3(0, 0, 10));
    testCluster->objectInfo().setName("basicship");
    testCluster->objectInfo().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);

    m_player.setShip(testCluster);

    WorldObject *wall = new WorldObject(1);
    wall->move(glm::vec3(-30, 0, -50));
    wall->rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 15; y++) {
            for(int z = 0; z < 3; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
            }
        }
    }
    wall->objectInfo().setName("Wall");
    wall->objectInfo().setShowOnHud(true);
    wall->objectInfo().setCanLockOn(true);
    m_world->god().scheduleSpawn(wall);

    glow::debug("Create Planet");
    WorldObject *planet = new WorldObject();
    planet->move(glm::vec3(20, 10, -30));
    int diameter = 24;
    glm::vec3 middle(diameter/2, diameter/2, diameter/2);
    for(int x = 0; x < diameter; x++) {
        for(int y = 0; y < diameter; y++) {
            for(int z = 0; z < diameter; z++) {
                glm::vec3 cell(x, y, z);

                if(glm::length(cell - middle) < diameter/2) {
                    planet->addVoxel(new Voxel(glm::ivec3(x, y, z), 0x0055AA));
                }
            }
        }
    }
    planet->setCrucialVoxel(glm::ivec3(middle));
    planet->objectInfo().setName("Planet");
    planet->objectInfo().setShowOnHud(true);
    planet->objectInfo().setCanLockOn(true);
    m_world->god().scheduleSpawn(planet);


    for(int e = 0; e < 15; e++) {
        WorldObject *enemy = new WorldObject();
        int r = 80;
        enemy->move(glm::vec3(-80 + rand()%r-r/2,rand()%r-r/2,-20 + rand()%r-r/2));

        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 2; y++) {
                for(int z = 0; z < 8; z++) {
                    enemy->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xF0FF00));
                }
            }
        }
        enemy->objectInfo().setName("enemy");
        enemy->objectInfo().setShowOnHud(false);
        enemy->objectInfo().setCanLockOn(false);
        m_world->god().scheduleSpawn(enemy);

    }


    glow::debug("Initial spawn");
    m_world->god().spawn();

    m_hd3000dummy = std::unique_ptr<HD3000Dummy>(new HD3000Dummy);

    m_out = new StreamRedirect(std::cout, &m_player.hud(), true);
    m_err = new StreamRedirect(std::cerr, &m_player.hud(), true);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
    glow::debug("Game::initialize Done");
}


void Game::update(float deltaSec) {
    // skip non-updates
    if (deltaSec == 0) return;

    //if (deltaSec < 1 / 60) deltaSec = 1 / 60;
    // avoid big jumps after debugging ;)
    deltaSec = glm::min(1.f, deltaSec);

    World::instance()->update(deltaSec);
    m_player.update(deltaSec);
    m_inputHandler.update(deltaSec);

//	m_hud->update(deltaSec);
}

void Game::draw() {
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_DEPTH_BUFFER_BIT);

    m_player.draw();

    m_hd3000dummy->drawIfActive();
}

InputHandler& Game::inputHandler() {
    return m_inputHandler;
}

