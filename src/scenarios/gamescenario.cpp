#include "gamescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/flytotask.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/grouptasks/defendareatask.h"
#include "ai/basictasks/formationmembertask.h"
#include "ai/squadlogic.h"
#include "ai/squad.h"

#include "equipment/engineslot.h"
#include "equipment/hardpoint.h"
#include "equipment/weapons/gun.h"

#include "factions/factionmatrix.h"

#include "resource/worldobjectbuilder.h"

#include "worldobject/ship.h"
#include "sound/soundmanager.h"
#include "gamestate/gameplay/gameplay.h"
#include "world/world.h"
#include "voxel/voxel.h"
#include "world/god.h"
#include "player.h"
#include "worldobject/worldobjectinfo.h"


GameScenario::GameScenario(GamePlay* gamePlay):
    BaseScenario(gamePlay)
{
}

void GameScenario::populateWorld() {
    glow::debug("Create WorldObjects");

    spawnPoliceFleet();

    spawnPirateFleet();

    Ship *testCluster = WorldObjectBuilder("f302").buildShip();
    testCluster->transform().setPosition(glm::vec3(0, 0, 10));
    testCluster->info().setName("player");
    testCluster->info().setShowOnHud(false);
    m_world->god().scheduleSpawn(testCluster);
    World::instance()->player().setShip(testCluster);

    spawnStuff();

    glow::debug("Initial spawn");
    m_world->god().spawn();
}

void GameScenario::createArmada() {
    std::shared_ptr<Squad> armada = std::make_shared<Squad>();
    armada->setTask(std::make_shared<DefendAreaTask>(*armada,
        std::list<glm::vec3>{
            glm::vec3(900, 0, 0),
            glm::vec3(1500, 0, 0),
            glm::vec3(1400, 500, 0),
        }, 500.0f));

    Ship* chief = WorldObjectBuilder("normandy").buildShip();
    chief->transform().setPosition(glm::vec3(700, 0, 0));
    chief->info().setName("Normandy");
    chief->info().setShowOnHud(true);
    chief->info().setCanLockOn(true);
    chief->squadLogic()->joinSquad(armada);
    chief->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    m_world->god().scheduleSpawn(chief);

    int memberCount = 12;
    for (int i = 0; i < memberCount; i++) {
        Ship *follower = i < 6 ? WorldObjectBuilder("mox").buildShip() : WorldObjectBuilder("smallpolice").buildShip();
        follower->transform().setPosition(glm::vec3(700, 50* (-memberCount / 2.0f + i), 0));
        follower->info().setName("member");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquad(armada);
        follower->character()->setFaction(World::instance()->factionMatrix().policeFaction());
        m_world->god().scheduleSpawn(follower);
    }

}

void GameScenario::spawnPoliceFleet() {
    createArmada();

    std::shared_ptr<Squad> squadA = std::make_shared<Squad>();
    squadA->setTask(std::make_shared<DefendAreaTask>(*squadA,
        std::list<glm::vec3>{ glm::vec3(400, 0, 200), glm::vec3(-400, 0, -400),
        glm::vec3(-600, 0, -400), glm::vec3(0, 100, -600),
        glm::vec3(-100, 150, -900) }, 500.0f));

    Ship* capital = WorldObjectBuilder("c306").buildShip();
    capital->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    capital->transform().setPosition(glm::vec3(0, 0, -200));
    capital->info().setName("Capital");
    capital->info().setShowOnHud(true);
    capital->info().setCanLockOn(true);
    capital->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(capital);

    Ship* cruiser = WorldObjectBuilder("bc304").buildShip();
    cruiser->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    cruiser->transform().setPosition(glm::vec3(-50, -50, -100));
    cruiser->info().setName("Cruiser");
    cruiser->info().setShowOnHud(true);
    cruiser->info().setCanLockOn(true);
    cruiser->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(cruiser);

    int nmember_count = 5;
    for (int i = 0; i < nmember_count; i++) {
        Ship *follower = WorldObjectBuilder("f302").buildShip();
        follower->transform().setPosition(glm::vec3(100 * (-nmember_count / 2.0f + i), 50, 0));
        follower->character()->setFaction(World::instance()->factionMatrix().policeFaction());
        follower->info().setName("Fighter");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquad(squadA);
        m_world->god().scheduleSpawn(follower);
    }
}

void GameScenario::spawnPirateFleet() {
    std::shared_ptr<Squad> squadB = std::make_shared<Squad>();
    squadB->setTask(std::make_shared<DefendAreaTask>(*squadB,
        std::list<glm::vec3>{ glm::vec3(500, 0, 500), glm::vec3(500, 0, -500),
        glm::vec3(-500, 0, -500), glm::vec3(-500, 0, 500) }, 500.0f));

    Ship *leader = WorldObjectBuilder("pirateheavy").buildShip();
    leader->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader->transform().setPosition(glm::vec3(0, 200, -1000));
    leader->info().setName("pirate heavy");
    leader->info().setShowOnHud(true);
    leader->info().setCanLockOn(true);
    leader->squadLogic()->joinSquad(squadB);
    m_world->god().scheduleSpawn(leader);

    int lmember_count = 15;
    for (int i = 0; i < lmember_count; i++) {
        Ship *follower = WorldObjectBuilder("piratelight").buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(100 * (-lmember_count / 2.0f + i), 200, -1000));
        follower->info().setName("pirate light");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader);
        m_world->god().scheduleSpawn(follower);
    }

    std::shared_ptr<Squad> squadC = std::make_shared<Squad>();
    squadC->setTask(std::make_shared<DefendAreaTask>(*squadC,
        std::list<glm::vec3>{ glm::vec3(500, 0, 500), glm::vec3(500, 0, -500),
        glm::vec3(-500, 0, -500), glm::vec3(-500, 0, 500) }, 500.0f));

    Ship *leader2 = WorldObjectBuilder("piratefrigatte").buildShip();
    leader2->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader2->transform().setPosition(glm::vec3(100, -200, -1000));
    leader2->info().setName("pirate frigate");
    leader2->info().setShowOnHud(true);
    leader2->info().setCanLockOn(true);
    leader2->squadLogic()->joinSquad(squadC);
    m_world->god().scheduleSpawn(leader2);

    int lmember_count2 = 7;
    for (int i = 0; i < lmember_count2; i++) {
        Ship *follower = WorldObjectBuilder("pirategunboat").buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(200 * (-lmember_count / 2.0f + i), -200, -1000));
        follower->info().setName("pirate gunboat");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader2);
        m_world->god().scheduleSpawn(follower);
    }
}

void GameScenario::spawnStuff() {
    WorldObject *wall = new WorldObject();
    wall->transform().move(glm::vec3(-30, 0, -50));
    wall->transform().rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 15; y++) {
            for (int z = 0; z < 3; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878FF));
            }
        }
    }
    wall->info().setName("Wall");
    wall->info().setShowOnHud(true);
    wall->info().setCanLockOn(true);
    m_world->god().scheduleSpawn(wall);

    WorldObject *planet = new WorldObject();
    planet->transform().move(glm::vec3(20, 10, -30));
    int diameter = 24;
    glm::vec3 middle(diameter / 2, diameter / 2, diameter / 2);
    for (int x = 0; x < diameter; x++) {
        for (int y = 0; y < diameter; y++) {
            for (int z = 0; z < diameter; z++) {
                glm::vec3 cell(x, y, z);

                if (glm::length(cell - middle) < diameter / 2) {
                    planet->addVoxel(new Voxel(glm::ivec3(x, y, z), 0x0055AAFF));
                }
            }
        }
    }
    planet->setCrucialVoxel(glm::ivec3(middle));
    planet->info().setName("Planet");
    m_world->god().scheduleSpawn(planet);

    for (int e = 0; e < 15; e++) {
        WorldObject *enemy = new WorldObject();
        int r = 80;
        enemy->transform().move(glm::vec3(-80 + rand() % r - r / 2, rand() % r - r / 2, -20 + rand() % r - r / 2));

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 2; y++) {
                for (int z = 0; z < 8; z++) {
                    enemy->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xF0FF00FF));
                }
            }
        }
        enemy->info().setName("dummy");
        enemy->info().setShowOnHud(false);
        enemy->info().setCanLockOn(false);
        m_world->god().scheduleSpawn(enemy);

    }
}

