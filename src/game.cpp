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
#include "ai/elevatedtasks/followtask.h"
#include "ai/basictasks/fight.h"


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
    glow::AutoTimer t("Initialize Game");

    glow::debug("Game::testFMOD()");
    //testFMOD();

    //Must be created first
    m_linuxvmdummy = std::unique_ptr<LinuxVMDummy>(new LinuxVMDummy);

    glow::debug("create world");
    m_world = World::instance();

    glow::debug("Create Skybox");
    m_skybox = std::unique_ptr<Skybox>(new Skybox);

    m_voxelRenderer = VoxelRenderer::instance();


    glow::debug("Create WorldObjects");
    Ship *normandy = new Ship();
    ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
    normandy->setPosition(glm::vec3(0, 0, -100));
    normandy->objectInfo().setName("Normandy");
    normandy->objectInfo().setShowOnHud(true);
    normandy->objectInfo().setCanLockOn(true);
    //m_world->god().scheduleSpawn(normandy);
    normandy->setCharacter(
        new DummyCharacter(*normandy, new DummyElevatedTask(*normandy, new BasicTask(*normandy)))
    );

    Ship *playerShip = new Ship();
    ClusterCache::instance()->fillObject(playerShip, "data/voxelcluster/basicship.csv");
    playerShip->setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    m_world->god().scheduleSpawn(playerShip);
    m_player.setShip(playerShip);

    Ship *aitester = new Ship();
    ClusterCache::instance()->fillObject(aitester, "data/voxelcluster/basicship.csv");
    aitester->setPosition(glm::vec3(40, 0, -500));
    aitester->objectInfo().setName("follower");
    aitester->objectInfo().setShowOnHud(true);
    m_world->god().scheduleSpawn(aitester);

    WorldObject *wall = new WorldObject(1);
    wall->move(glm::vec3(-30, 0, -50));
    wall->rotate(glm::angleAxis(glm::radians(-90.f), glm::vec3(0, 1, 0)));
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
    //m_world->god().scheduleSpawn(wall);

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
    //m_world->god().scheduleSpawn(planet);

    Ship* previous = normandy;
    std::list<std::shared_ptr<WorldObjectHandle>> enemies1;
    std::list<std::shared_ptr<WorldObjectHandle>> enemies2;
    for (int e = 0; e < 50; e++) {
        Ship *enemy = new Ship();
        int r = 200;
        enemy->move(glm::vec3(-200 + rand() % r - r / 2, rand() % r - r / 2, -200 + rand() % r - r / 2));
        enemy->objectInfo().setName("enemy2");
        enemy->objectInfo().setShowOnHud(false);
        enemy->objectInfo().setCanLockOn(false);
        ClusterCache::instance()->fillObject(enemy, "data/voxelcluster/basicship.csv");
        m_world->god().scheduleSpawn(enemy);
        enemies2.push_back(enemy->handle());
    }
    for (int e = 0; e < 50; e++) {
        Ship *enemy = new Ship();
        int r = 200;
        enemy->move(glm::vec3(200 + rand() % r - r / 2, rand() % r - r / 2, -200 + rand() % r - r / 2));
        enemy->objectInfo().setName("enemy1");
        enemy->objectInfo().setShowOnHud(false);
        enemy->objectInfo().setCanLockOn(false);
        ClusterCache::instance()->fillObject(enemy, "data/voxelcluster/basicship.csv");
        m_world->god().scheduleSpawn(enemy);
        enemies1.push_back(enemy->handle());
    }
    for (std::shared_ptr<WorldObjectHandle> handle : enemies1) {

        std::vector<std::shared_ptr<WorldObjectHandle>> tmpVector(enemies2.size());
        std::copy(enemies2.begin(), enemies2.end(), tmpVector.begin());
        std::random_shuffle(tmpVector.begin(), tmpVector.end());
        copy(tmpVector.begin(), tmpVector.end(), enemies2.begin());

        Ship* e = (Ship*)handle->get();
        e->setCharacter(new DummyCharacter(*e, new DummyElevatedTask(*e, new Fight(*e, enemies2))));
    }
    for (std::shared_ptr<WorldObjectHandle> handle : enemies2) {
        std::vector<std::shared_ptr<WorldObjectHandle>> tmpVector(enemies1.size());
        std::copy(enemies1.begin(), enemies1.end(), tmpVector.begin());
        std::random_shuffle(tmpVector.begin(), tmpVector.end());
        copy(tmpVector.begin(), tmpVector.end(), enemies1.begin());

        Ship* e = (Ship*)handle->get();
        e->setCharacter(new DummyCharacter(*e, new DummyElevatedTask(*e, new Fight(*e, enemies1))));
    }

    aitester->setCharacter(new DummyCharacter(*aitester, new DummyElevatedTask(*aitester, new Fight(*aitester, std::list<std::shared_ptr<WorldObjectHandle>>{playerShip->handle()}))));


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

    //if (deltaSec < 1 / 60) deltaSec = 1 / 60;
    // avoid big jumps after debugging ;)
    deltaSec = glm::min(1.f, deltaSec);

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
/*
void ERRCHECK(FMOD_RESULT result) {
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}
*/
void Game::testFMOD() {
    /*
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
    */
}

InputHandler* Game::inputHandler() {
    return m_inputHandler.get();
}

