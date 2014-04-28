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

#include "resource/worldelementbuilder.h"

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

    Ship *testCluster = WorldElementBuilder("mox").buildShip();
    testCluster->transform().setPosition(glm::vec3(100, 140, 50));
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
            glm::vec3(300, 0, 0),
            glm::vec3(1500, 0, 0),
            glm::vec3(1400, 500, 0),
        }, 500.0f));

    Ship* chief = WorldElementBuilder("normandy").buildShip();
    chief->transform().setPosition(glm::vec3(700, 0, 0));
    chief->info().setName("Normandy");
    chief->info().setShowOnHud(true);
    chief->info().setCanLockOn(true);
    chief->squadLogic()->joinSquad(armada);
    chief->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    m_world->god().scheduleSpawn(chief);

    int memberCount = 8;
    for (int i = 0; i < memberCount; i++) {
        Ship *follower = i < 6 ? WorldElementBuilder("mox").buildShip() : WorldElementBuilder("smallpolice").buildShip();
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

    Ship* capital = WorldElementBuilder("normandy").buildShip();
    capital->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    capital->transform().setPosition(glm::vec3(0, 0, -200));
    capital->info().setName("Capital");
    capital->info().setShowOnHud(true);
    capital->info().setCanLockOn(true);
    capital->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(capital);

    Ship* cruiser = WorldElementBuilder("bc304").buildShip();
    cruiser->character()->setFaction(World::instance()->factionMatrix().policeFaction());
    cruiser->transform().setPosition(glm::vec3(-50, -50, -100));
    cruiser->info().setName("Cruiser");
    cruiser->info().setShowOnHud(true);
    cruiser->info().setCanLockOn(true);
    cruiser->squadLogic()->joinSquad(squadA);
    m_world->god().scheduleSpawn(cruiser);

    int nmember_count = 14;
    for (int i = 0; i < nmember_count; i++) {
        std::string type = i < 6 ? (i < 3 ? "mox" : "f302") : "f301";
        Ship *follower = WorldElementBuilder(type).buildShip();
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

    Ship *leader = WorldElementBuilder("pirateheavy").buildShip();
    leader->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader->transform().setPosition(glm::vec3(0, 200, -1000));
    leader->info().setName("pirate heavy");
    leader->info().setShowOnHud(true);
    leader->info().setCanLockOn(true);
    leader->squadLogic()->joinSquad(squadB);
    m_world->god().scheduleSpawn(leader);

    int lmember_count = 6;
    for (int i = 0; i < lmember_count; i++) {
        Ship *follower = WorldElementBuilder("piratelight").buildShip();
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

    Ship *leader2 = WorldElementBuilder("piratefrigatte").buildShip();
    leader2->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader2->transform().setPosition(glm::vec3(100, -200, -1000));
    leader2->info().setName("pirate frigate");
    leader2->info().setShowOnHud(true);
    leader2->info().setCanLockOn(true);
    leader2->squadLogic()->joinSquad(squadC);
    m_world->god().scheduleSpawn(leader2);

    int lmember_count2 = 8;
    for (int i = 0; i < lmember_count2; i++) {
        std::string type = i < 2 ? "pirategunboat" : "piratelight";

        Ship *follower = WorldElementBuilder(type).buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(200 * (-lmember_count / 2.0f + i), -200, -1000));
        follower->info().setName("pirate");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader2);
        m_world->god().scheduleSpawn(follower);
    }

    std::shared_ptr<Squad> squadD = std::make_shared<Squad>();
    squadD->setTask(std::make_shared<DefendAreaTask>(*squadD,
        std::list<glm::vec3>{ glm::vec3(400, 0, 200), glm::vec3(-400, 0, -400),
        glm::vec3(-600, 0, -400), glm::vec3(0, 100, -600),
        glm::vec3(-100, 150, -900)}, 500.0f));

    Ship *leader3 = WorldElementBuilder("piratelight").buildShip();
    leader3->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader3->transform().setPosition(glm::vec3(-1000, -200, -2400));
    leader3->info().setName("pirate frigate");
    leader3->info().setShowOnHud(true);
    leader3->info().setCanLockOn(true);
    leader3->squadLogic()->joinSquad(squadD);
    m_world->god().scheduleSpawn(leader3);

    int lmember_count3 = 5;
    for (int i = 0; i < lmember_count3; i++) {
        Ship *follower = WorldElementBuilder("piratelight").buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(-1000 * (-lmember_count / 2.0f + i), -200, -1700));
        follower->info().setName("pirate");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader3);
        m_world->god().scheduleSpawn(follower);
    }

    std::shared_ptr<Squad> squadE = std::make_shared<Squad>();
    squadE->setTask(std::make_shared<DefendAreaTask>(*squadE,
        std::list<glm::vec3>{ glm::vec3(0, 0, 0), glm::vec3(700, 0, 700) }, 1500.0f));

    Ship *leader4 = WorldElementBuilder("piratelight").buildShip();
    leader4->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
    leader4->transform().setPosition(glm::vec3(1000, -200, -3500));
    leader4->info().setName("pirate frigate");
    leader4->info().setShowOnHud(true);
    leader4->info().setCanLockOn(true);
    leader4->squadLogic()->joinSquad(squadE);
    m_world->god().scheduleSpawn(leader4);

    int lmember_count4 = 15;
    for (int i = 0; i < lmember_count3; i++) {
        Ship *follower = WorldElementBuilder("piratelight").buildShip();
        follower->character()->setFaction(World::instance()->factionMatrix().pirateFaction());
        follower->transform().setPosition(glm::vec3(1000 * (-lmember_count / 2.0f + i), -200, -3700));
        follower->info().setName("pirate");
        follower->info().setShowOnHud(true);
        follower->info().setCanLockOn(true);
        follower->squadLogic()->joinSquadOf(leader4);
        m_world->god().scheduleSpawn(follower);
    }
}

void GameScenario::spawnStuff() {

}

