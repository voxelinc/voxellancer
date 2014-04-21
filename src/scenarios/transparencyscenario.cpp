#include "transparencyscenario.h"

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


TransparencyScenario::TransparencyScenario(GamePlay* inGame) :
    BaseScenario(inGame)
{
}

void TransparencyScenario::populateWorld() {
    glow::debug("Create WorldObjects");
    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();
    
    Ship *testCluster = WorldObjectBuilder("basicship").buildShip();
    testCluster->transform().setPosition(glm::vec3(0, 0, 10));
    testCluster->info().setName("basicship");
    testCluster->info().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);

    World::instance()->player().setShip(testCluster);

    WorldObject *wall = new WorldObject();
    for(int x = 0; x < 60; x++) {
        for(int y = 0; y < 50; y++) {
            for(int z = 0; z < 5; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xB4787830));
            }
        }
    }
    wall->transform().setPosition(glm::vec3(0, 10, -10));
    wall->info().setName("Wall");
    wall->info().setShowOnHud(true);
    wall->info().setCanLockOn(true);
    m_world->god().scheduleSpawn(wall);

    glow::debug("Create Planet");
    WorldObject *planet = new WorldObject();
    int diameter = 50;
    glm::vec3 middle(diameter/2, diameter/2, diameter/2);
    for(int x = 0; x < diameter; x++) {
        for(int y = 0; y < diameter; y++) {
            for(int z = 0; z < diameter; z++) {
                glm::vec3 cell(x, y, z);

                if(glm::length(cell - middle) < diameter/2) {
                    planet->addVoxel(new Voxel(glm::ivec3(x, y, z), 0x0055AA80));
                }
            }
        }
    }
    planet->transform().setPosition(glm::vec3(0, 10, -50));
    planet->setCrucialVoxel(glm::ivec3(middle));
    planet->info().setName("Planet");
    planet->info().setShowOnHud(true);
    planet->info().setCanLockOn(true);
    m_world->god().scheduleSpawn(planet);

    for(int e = 0; e < 15; e++) {
        WorldObject *enemy = new WorldObject();
        int r = 80;
        enemy->transform().move(glm::vec3(rand()%r-r/2,rand()%r-r/2,rand()%r-r/2));

        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 2; y++) {
                for(int z = 0; z < 8; z++) {
                    enemy->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xF0FF0070));
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

