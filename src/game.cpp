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
#include "resource/clusterstore.h"
#include "utils/hd3000dummy.h"
#include "utils/linuxvmdummy.h"
#include "voxel/voxelrenderer.h"
#include "ui/inputhandler.h"
#include "ui/hud.h"
#include "skybox.h"

Game::Game(GLFWwindow *window):
	m_window(window),
	m_camera(),
	m_inputHandler(window, &m_camera, &m_testClusterMoveable),
	m_collisionDetector(m_worldtree, m_testClusterMoveable),
	m_testClusterA(0),
	m_testClusterB(0)
{
	reloadConfig();
}

Game::~Game(){
	delete m_testClusterA;
	delete m_testClusterB;
}

void Game::reloadConfig(){
#ifdef WIN32
	PropertyManager::instance()->load("data/config.ini");
#endif
}

void Game::initialize()
{
    glow::AutoTimer t("Initialize Game");

	glow::debug("Game::testFMOD()");
    //testFMOD();

	//Must be created first
	m_linuxvmdummy = std::unique_ptr<LinuxVMDummy>(new LinuxVMDummy);

	glow::debug("Create Skybox");
	m_skybox = std::unique_ptr<Skybox>(new Skybox);

	glow::debug("Create Voxel");
    m_voxelRenderer = std::unique_ptr<VoxelRenderer>(new VoxelRenderer);

    m_testCluster.transform().move(glm::vec3(0, 0, 0));
    m_testCluster.applyTransform(false);
    m_testCluster.addVoxel(Voxel(cvec3(1, 0, 0), cvec3(0, 255, 0), &m_testCluster));
    m_testCluster.addVoxel(Voxel(cvec3(2, 0, 0), cvec3(255, 255, 0), &m_testCluster));
    m_testCluster.addVoxel(Voxel(cvec3(1, 1, 0), cvec3(0, 0, 255), &m_testCluster));
    m_testCluster.addVoxel(Voxel(cvec3(1, 0, 1), cvec3(255, 0, 0), &m_testCluster));
    m_testCluster.addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 0, 128), &m_testCluster));
    m_worldtree.insert(&m_testCluster);

    m_testClusterMoveable.transform().setCenter(glm::vec3(0,0,7));
    m_testClusterMoveable.transform().move(glm::vec3(-20, 0, 0));
    m_testClusterMoveable.transform().rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    m_testClusterMoveable.applyTransform(false);
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 7), cvec3(0, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 6), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 5), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 4), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 3), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 2), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 1), cvec3(255, 255, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(1, 1, 7), cvec3(0, 0, 255), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(1, 0, 7), cvec3(255, 0, 0), &m_testClusterMoveable));
    m_testClusterMoveable.addVoxel(Voxel(cvec3(0, 0, 8), cvec3(255, 0, 128), &m_testClusterMoveable));
    m_worldtree.insert(&m_testClusterMoveable);

	m_testClusterA = ClusterStore::instance()->create("data/voxelcluster/normandy.csv");
	m_testClusterA->transform().setCenter(glm::vec3(21, 8, 40));
	m_testClusterA->transform().setPosition(glm::vec3(0, 0, -100));
	m_testClusterA->applyTransform(false);

	m_testClusterB = ClusterStore::instance()->create("data/voxelcluster/basicship.csv");
	m_testClusterB->transform().setCenter(glm::vec3(3, 0, 3));
	m_testClusterB->transform().setPosition(glm::vec3(0, 0, 10));
	m_testClusterB->applyTransform(false);

	m_worldtree.insert(m_testClusterA);
    m_worldtree.insert(m_testClusterB);

	glow::debug("Setup Camera");
	//viewport set in resize
	m_camera.setPosition(glm::vec3(0, 5, 30));
	m_camera.setZNear(1);
	m_camera.setZFar(9999);

	glow::debug("Create HUD");
	m_hud = std::unique_ptr<HUD>(new HUD(std::list<VoxelCluster*>{ m_testClusterA, m_testClusterB, &m_testCluster, &m_testClusterMoveable }));
	m_hud->setCamera(&m_camera);

    m_hd3000dummy = std::unique_ptr<HD3000Dummy>(new HD3000Dummy);

    glClearColor(0.2f, 0.3f, 0.4f, 1.f);
	glow::debug("Game::initialize Done");
}

static int last_collisions = 0;

void Game::update(float delta_sec)
{
    std::list<Collision> collisions = m_collisionDetector.checkCollisions();
    if (collisions.size() != last_collisions) {
        glow::debug("Collisions: %;", collisions.size());
        last_collisions = collisions.size();
    }

	m_inputHandler.update(delta_sec);

    // TODO: use god instead
    m_testCluster.applyTransform();
    m_testClusterA->applyTransform();
    m_testClusterB->applyTransform();
    m_testClusterMoveable.applyTransform();
	m_hud->update(delta_sec);
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	m_skybox->draw(&m_camera);

    m_voxelRenderer->prepareDraw(&m_camera);
    m_voxelRenderer->draw(&m_testCluster);
    m_voxelRenderer->draw(&m_testClusterMoveable);
	m_voxelRenderer->draw(m_testClusterA);
	m_voxelRenderer->draw(m_testClusterB);

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



