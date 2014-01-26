#include "gamescenario.h"

#include <glm/glm.hpp>

#include <glow/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"

#include "game.h"


GameScenario::GameScenario() {

}

void GameScenario::populate(Game* game) {
    glow::AutoTimer t("Initialize Game");

    glow::debug("create world");
    World* world = World::instance();

    glow::debug("Create WorldObjects");
    m_normandy = new Ship();
    ClusterCache::instance()->fillObject(m_normandy, "data/voxelcluster/normandy.csv");
    m_normandy->setPosition(glm::vec3(0, 0, -100));
    m_normandy->objectInfo().setName("Normandy");
    m_normandy->objectInfo().setShowOnHud(true);
    m_normandy->objectInfo().setCanLockOn(true);
    world->god().scheduleSpawn(m_normandy);
    // TODO: use these dummies to test BasicTasks
    m_normandy->setCharacter(
        new DummyCharacter(*m_normandy,
        new DummyElevatedTask(*m_normandy,
        new BasicTask(*m_normandy))));

    Ship *testCluster = new Ship();
    ClusterCache::instance()->fillObject(testCluster, "data/voxelcluster/basicship.csv");
    testCluster->setPosition(glm::vec3(0, 0, 10));
    testCluster->objectInfo().setName("basicship");
    testCluster->objectInfo().setShowOnHud(false);
    world->god().scheduleSpawn(testCluster);

    m_aimTester = new Ship();
    ClusterCache::instance()->fillObject(m_aimTester, "data/voxelcluster/basicship.csv");
    m_aimTester->setPosition(glm::vec3(10, 0, -20));
    m_aimTester->rotate(glm::quat(glm::vec3(10, 0,0)));
    m_aimTester->objectInfo().setName("aimTester");
    m_aimTester->objectInfo().setShowOnHud(true);
    m_aimTester->objectInfo().setCanLockOn(true);
    world->god().scheduleSpawn(m_aimTester);

    game->player().setShip(testCluster);

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
    world->god().scheduleSpawn(wall);

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
    world->god().scheduleSpawn(planet);

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
        world->god().scheduleSpawn(enemy);

    }

    glow::debug("Initial spawn");
    world->god().spawn();
}

void GameScenario::update(float deltaSec) {
    m_normandy->accelerate(glm::vec3(0, 0, -0.3f));
    m_normandy->accelerateAngular(glm::vec3(0.1f, 0.05f, 0.0f));
    m_aimTester->accelerate(glm::vec3(0, 0, -0.4f));
    m_aimTester->accelerateAngular(glm::vec3(0.0f, 0.0f, 0.4f));
}

