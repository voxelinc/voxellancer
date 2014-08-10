#include "frozengamescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/flytotask.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/basictasks/formationmembertask.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"

#include "resource/clustercache.h"
#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"
#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"

#include "sound/soundmanager.h"
#include "gamestate/gameplay/gameplay.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"
#include "player.h"
#include "worldobject/worldobjectinfo.h"


FrozenGameScenario::FrozenGameScenario(GamePlay* inGame) :
    BaseScenario(inGame)
{
}

void FrozenGameScenario::populateWorld() {
    glow::debug("Create WorldObjects");
    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();

    Ship* normandy = WorldObjectBuilder("normandy").buildShip();
    normandy->transform().setPosition(glm::vec3(0, 0, -100));
    normandy->info().setName("Normandy");
    normandy->info().setShowOnHud(true);
    normandy->info().setCanLockOn(true);
    normandy->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(normandy);

    int nmember_count = 4;
    for (int i = 0; i < nmember_count; i++) {
        Ship *follower = WorldObjectBuilder("basicship").buildShip();
        follower->transform().setPosition(glm::vec3(100 * (-nmember_count / 2.0f + i), 50, 0));
        follower->info().setName("member");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquad(squadA);
        m_world->god().scheduleSpawn(follower);
    }


    std::shared_ptr<Squad> squadB = std::make_shared<Squad>();

    Ship *leader = WorldObjectBuilder("eagle").buildShip();
    leader->transform().setPosition(glm::vec3(0, 200, -100));
    leader->info().setName("leader");
    leader->info().setShowOnHud(true);
    leader->info().setCanLockOn(true);
    leader->squadLogic()->joinSquad(squadB);
    m_world->god().scheduleSpawn(leader);

    int lmember_count = 2;
    for (int i = 0; i < lmember_count; i++) {
        Ship *follower = WorldObjectBuilder("basicship").buildShip();
        follower->transform().setPosition(glm::vec3(100 * (-lmember_count / 2.0f + i), 200, 0));
        follower->info().setName("member");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader);
        m_world->god().scheduleSpawn(follower);
    }

    Ship *testCluster = WorldObjectBuilder("mox").buildShip();
    testCluster->transform().setPosition(glm::vec3(0, 0, 10));
    testCluster->info().setName("basicship");
    testCluster->info().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);

    World::instance()->player().setShip(testCluster);

    WorldObject *wall = new WorldObject();
    wall->transform().move(glm::vec3(-30, 0, -50));
    wall->transform().rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    for(int x = 0; x < 20; x++) {
        for(int y = 0; y < 15; y++) {
            for(int z = 0; z < 3; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
            }
        }
    }
    wall->info().setName("Wall");
    wall->info().setShowOnHud(true);
    wall->info().setCanLockOn(true);
    m_world->god().scheduleSpawn(wall);

    glow::debug("Create Planet");
    WorldObject *planet = new WorldObject();
    planet->transform().move(glm::vec3(20, 10, -30));
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
    planet->info().setName("Planet");
    planet->info().setShowOnHud(true);
    planet->info().setCanLockOn(true);
    m_world->god().scheduleSpawn(planet);

    for(int e = 0; e < 15; e++) {
        WorldObject *enemy = new WorldObject();
        int r = 80;
        enemy->transform().move(glm::vec3(-80 + rand()%r-r/2,rand()%r-r/2,-20 + rand()%r-r/2));

        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 2; y++) {
                for(int z = 0; z < 8; z++) {
                    enemy->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xF0FF00));
                }
            }
        }
        enemy->info().setName("enemy");
        enemy->info().setShowOnHud(false);
        enemy->info().setCanLockOn(false);
        m_world->god().scheduleSpawn(enemy);

    }

    glow::debug("Initial spawn");
    m_world->god().spawn();
}

