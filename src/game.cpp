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

#include <fmod.hpp>
#include <fmod_dsp.h>
#include <fmod_errors.h>

#include "property/propertymanager.h"
#include "resource/clustercache.h"
#include "utils/hd3000dummy.h"
#include "utils/linuxvmdummy.h"
#include "ui/inputhandler.h"
#include "ui/hud.h"

#include "world/world.h"
#include "world/god.h"
#include "skybox.h"
#include "voxel/voxelrenderer.h"
#include "worldobject/ship.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"

class Ship;


Game::Game(GLFWwindow *window) :
    m_window(window),
    m_camera(),
    m_player(&m_camera),
    m_inputHandler(window, &m_player, &m_camera)
{
	reloadConfig();
}

Game::~Game(){

}

void Game::reloadConfig() {
	PropertyManager::instance()->load("data/config.ini");
}

void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");

	glow::debug("Game::testFMOD()");
    //testFMOD();

	//Must be created first
	m_linuxvmdummy = std::unique_ptr<LinuxVMDummy>(new LinuxVMDummy);

    glow::debug("create world");
    m_world = World::instance();
    m_treeStateReporter.setWorldTree(&m_world->worldTree());

    glow::debug("Create Skybox");
	m_skybox = std::unique_ptr<Skybox>(new Skybox);

	glow::debug("Create Voxel");
    m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer);


    WorldObject *testClusterMoveable = new WorldObject();
    testClusterMoveable->move(glm::vec3(-20, 0, 0));
    testClusterMoveable->rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 7), 0x00FF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 6), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 5), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 4), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 3), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 2), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 1), 0xFFFF00));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(1, 1, 7), 0x0000FF));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(1, 0, 7), 0xFF0000));
    testClusterMoveable->addVoxel(new Voxel(glm::ivec3(0, 0, 8), 0xFF0080));
    testClusterMoveable->finishInitialization();
    testClusterMoveable->objectInfo().setName("movable");
    m_world->god().scheduleSpawn(testClusterMoveable);

    //m_inputHandler.setVoxelCluster(m_testClusterMoveable);


    Ship *normandy = new Ship();
    ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
	normandy->setPosition(glm::vec3(0, 0, -100));
    normandy->finishInitialization();
    normandy->objectInfo().setName("Normandy");
    m_world->god().scheduleSpawn(normandy);

    Ship *testCluster = new Ship();
    ClusterCache::instance()->fillObject(testCluster, "data/voxelcluster/basicship.csv");
    testCluster->setPosition(glm::vec3(0, 0, 10));
    testCluster->finishInitialization();
    testCluster->objectInfo().setName("basicship");
    testCluster->objectInfo().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);

    m_player.setShip(testCluster);

    WorldObject *wall = new WorldObject(1);
    wall->move(glm::vec3(-20, 0, -50));
    wall->rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 15; y++) {
            for(int z = 0; z < 3; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
            }
        }
    }
    wall->finishInitialization();
    wall->objectInfo().setName("Wall");
    m_world->god().scheduleSpawn(wall);

    WorldObject *planet = new WorldObject();
    planet->move(glm::vec3(20, 10, -30));
    int diameter = 28;
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
    planet->finishInitialization();
    planet->objectInfo().setName("Planet");
    m_world->god().scheduleSpawn(planet);

    glow::debug("Initial spawn");
    m_world->god().spawn();

	glow::debug("Setup Camera");
	//viewport set in resize
	//m_camera.setPosition(glm::vec3(0, 5, 30));
	m_camera.setZNear(1);
	m_camera.setZFar(9999);

	glow::debug("Create HUD");
	m_hud = std::unique_ptr<HUD>(new HUD(&m_player));
	m_hud->setCamera(&m_camera);

    m_hd3000dummy = std::unique_ptr<HD3000Dummy>(new HD3000Dummy);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
	glow::debug("Game::initialize Done");
}


void Game::update(float delta_sec)
{
    // skip non-updates
    if (delta_sec == 0) return;

    //if (delta_sec < 1 / 60) delta_sec = 1 / 60;
    // avoid big jumps after debugging ;)
    delta_sec = glm::min(1.f, delta_sec);

    //m_treeStateReporter.nudge();

    m_inputHandler.update(delta_sec);
    World::instance()->update(delta_sec);
    m_player.setFollowCam();
	m_hud->update(delta_sec);
}

void Game::draw()
{
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


	m_hud->draw();

    m_hd3000dummy->drawIfActive();
}

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void Game::testFMOD()
{
    FMOD::System * system = 0;
    FMOD::Sound  * sound = 0;
    FMOD::Channel *channel = 0;

    FMOD_RESULT result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("data/LASER.mp3", FMOD_SOFTWARE, 0, &sound);
    ERRCHECK(result);

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);
}

InputHandler * Game::inputHandler()
{
    return &m_inputHandler;
}

TreeStateReporter::TreeStateReporter():
    TimedTask(std::chrono::duration<float>(1.5f)),
    m_worldTree(nullptr)
{

}

void TreeStateReporter::setWorldTree(WorldTree *worldTree) {
    m_worldTree = worldTree;
}

void TreeStateReporter::exec() {
    int nodes, empty, geodes, depth;
    m_worldTree->poll(nodes, empty, geodes, depth);
    std::cout << "WorldTree: " << nodes << " nodes; " << empty << " empty; " << geodes << " geodes; " << depth << " maxdepth" << std::endl;
    m_worldTree->print();
}


