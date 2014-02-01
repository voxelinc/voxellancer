#include "gamescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/basictasks/flytotask.h"
#include "ai/basictasks/patrolwaypointstask.h"
#include "ai/basictasks/formationmembertask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"
#include "game.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"

GameScenario::GameScenario() {

}

void GameScenario::populate(Game* game) {
    glowutils::AutoTimer t("Initialize Game");
    
    glow::debug("create world");
    World* world = World::instance();

    glow::debug("Create WorldObjects");
    Ship *normandy = new Ship();
    ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
    normandy->setPosition(glm::vec3(0, 0, -100));
    normandy->objectInfo().setName("Normandy");
    normandy->objectInfo().setShowOnHud(true);
    normandy->objectInfo().setCanLockOn(true);
    normandy->setEngineSound(SoundManager::current()->create("data/sound/Rocket Thrusters.ogg"));
    world->god().scheduleSpawn(normandy);
    PatrolWaypointsTask* ta = new PatrolWaypointsTask(*normandy,
        std::list<glm::vec3>{ glm::vec3(400, 0, 200), glm::vec3(-400, 0, -400), glm::vec3(-600, 0, -400), glm::vec3(0, 100, -600), glm::vec3(-100, 150, -900) });
    normandy->setCharacter(new DummyCharacter(*normandy, ta));

    int member_count = 4;
    for (int i = 0; i < member_count; i++) {
        Ship *follower = new Ship();
        ClusterCache::instance()->fillObject(follower, "data/voxelcluster/basicship.csv");
        follower->setPosition(glm::vec3(100 * (-member_count / 2.0f + i), 50, 0));
        follower->objectInfo().setName("member");
        follower->objectInfo().setShowOnHud(true);
        normandy->objectInfo().setCanLockOn(true);
        world->god().scheduleSpawn(follower);
        FormationMemberTask* task = new FormationMemberTask(*follower, normandy);
        follower->setCharacter(new DummyCharacter(*follower, task));
    }


    Ship *follower = new Ship();
    ClusterCache::instance()->fillObject(follower, "data/voxelcluster/basicship.csv");
    follower->setPosition(glm::vec3(100, 0, -50));
    follower->objectInfo().setName("follower");
    follower->objectInfo().setShowOnHud(true);
    world->god().scheduleSpawn(follower);
    FlyToTask* task = new FlyToTask(*follower);
    task->setTargetPoint(glm::vec3(-100, 0, -50));
    follower->setCharacter(new DummyCharacter(*follower, task));

    Ship *testCluster = new Ship();
    ClusterCache::instance()->fillObject(testCluster, "data/voxelcluster/basicship.csv");
    testCluster->setPosition(glm::vec3(0, 0, 10));
    testCluster->objectInfo().setName("basicship");
    testCluster->objectInfo().setShowOnHud(false);
    world->god().scheduleSpawn(testCluster);

    game->player().setShip(testCluster);
    testCluster->setCollideableWith(CollisionFilterClass::Rocket, false);

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
