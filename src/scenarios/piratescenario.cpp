#include "piratescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/flytotask.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/basictasks/formationmembertask.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"

#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"

#include "factions/factionmatrix.h"
#include "factions/policefaction.h"
#include "factions/piratefaction.h"

#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"
#include "gamestate/gameplay/gameplay.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"
#include "player.h"
#include "ui/objectinfo.h"


PirateScenario::PirateScenario(GamePlay* gamePlay) :
    BaseScenario(gamePlay)
{
}

void PirateScenario::populateWorld() {
    glow::debug("Create WorldObjects");

    createArmada();

    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();
    squadA->setTask(std::make_shared<PatrolWaypointsTask>(*squadA,
        std::list<glm::vec3>{ glm::vec3(400, 0, 200), glm::vec3(-400, 0, -400),
        glm::vec3(-600, 0, -400), glm::vec3(0, 100, -600),
        glm::vec3(-100, 150, -900) }));

    Ship* normandy = WorldObjectBuilder("piratefrigatte").buildShip();
    normandy->transform().setPosition(glm::vec3(0, 0, -100));
    normandy->objectInfo().setName("Frigatte");
    normandy->objectInfo().setShowOnHud(true);
    normandy->objectInfo().setCanLockOn(true);
    normandy->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(normandy);

    int nmember_count = 4;
    for (int i = 0; i < nmember_count; i++) {
        Ship *follower = WorldObjectBuilder("piratelight").buildShip();
        follower->transform().setPosition(glm::vec3(100 * (-nmember_count / 2.0f + i), 50, 0));
        follower->objectInfo().setName("Light");
        follower->objectInfo().setShowOnHud(true);
        follower->objectInfo().setCanLockOn(true);
        follower->squadLogic()->joinSquad(squadA);
        m_world->god().scheduleSpawn(follower);
    }


    std::shared_ptr<Squad> squadB = std::make_shared<Squad>();
    squadB->setTask(std::make_shared<PatrolWaypointsTask>(*squadB,
        std::list<glm::vec3>{ glm::vec3(500, 0, 500), glm::vec3(-500, 0, 500),
        glm::vec3(-500, 0, -500), glm::vec3(500, 0, -500) }));

    Ship *leader = WorldObjectBuilder("pirategunboat").buildShip();
    leader->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader->transform().setPosition(glm::vec3(0, 200, -100));
    leader->objectInfo().setName("leader");
    leader->objectInfo().setShowOnHud(true);
    leader->objectInfo().setCanLockOn(true);
    leader->squadLogic()->joinSquad(squadB);
    m_world->god().scheduleSpawn(leader);

    int lmember_count = 2;
    for (int i = 0; i < lmember_count; i++) {
        Ship *follower = WorldObjectBuilder("pirateheavy").buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(100 * (-lmember_count / 2.0f + i), 200, 0));
        follower->objectInfo().setName("member");
        follower->objectInfo().setShowOnHud(true);
        follower->objectInfo().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader);
        m_world->god().scheduleSpawn(follower);
    }

    Ship *testCluster = WorldObjectBuilder("pirateheavy").buildShip();
    testCluster->transform().setPosition(glm::vec3(0, 0, 10));
    testCluster->objectInfo().setName("basicship");
    testCluster->objectInfo().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);

    m_gamePlay->player().setShip(testCluster);

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
    wall->objectInfo().setName("Wall");
    wall->objectInfo().setShowOnHud(true);
    wall->objectInfo().setCanLockOn(true);
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
    planet->objectInfo().setName("Planet");
    m_world->god().scheduleSpawn(planet);

    glow::debug("Initial spawn");
    m_world->god().spawn();
}

void PirateScenario::createArmada() {
    std::shared_ptr<Squad> armada = std::make_shared<Squad>();
    armada->setTask(std::make_shared<PatrolWaypointsTask>(*armada,
        std::list<glm::vec3>{
            glm::vec3(900, 0, 0),
            glm::vec3(1500, 0, 0),
            glm::vec3(1400, 500, 0),
        }));

    Ship* chief = WorldObjectBuilder("normandy").buildShip();
    chief->transform().setPosition(glm::vec3(700, 0, 0));
    chief->objectInfo().setName("Normandy");
    chief->objectInfo().setShowOnHud(true);
    chief->objectInfo().setCanLockOn(true);
    chief->squadLogic()->joinSquad(armada);
    chief->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    m_world->god().scheduleSpawn(chief);

    int memberCount = 12;
    for (int i = 0; i < memberCount; i++) {
        Ship *follower = i < 6 ? WorldObjectBuilder("flyingtortress").buildShip() : WorldObjectBuilder("startortress").buildShip();
        follower->transform().setPosition(glm::vec3(700, 50* (-memberCount / 2.0f + i), 0));
        follower->objectInfo().setName("Turtle");
        follower->objectInfo().setShowOnHud(true);
        follower->objectInfo().setCanLockOn(true);
        follower->squadLogic()->joinSquad(armada);
        follower->character()->setFaction(World::instance()->factionMatrix().policeFaction());
        m_world->god().scheduleSpawn(follower);
    }

}
