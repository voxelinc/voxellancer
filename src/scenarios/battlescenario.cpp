#include "battlescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/fighttask.h"

#include "resource/worldobjectbuilder.h"

#include "equipment/hardpoint.h"
#include "equipment/engineslot.h"
#include "equipment/engine.h"
#include "equipment/weapon.h"
#include "equipment/weapons/gun.h"
#include "worldobject/ship.h"

#include "gamestate/gameplay/gameplay.h"
#include "sound/soundmanager.h"

#include "world/world.h"
#include "world/god.h"

#include "worldobject/worldobject.h"

#include "utils/randvec3.h"
#include "utils/handle/handle.h"
#include "player.h"
#include "worldobject/worldobjectinfo.h"


BattleScenario::BattleScenario(GamePlay* gamePlay):
    BaseScenario(gamePlay)
{

}

void BattleScenario::populateWorld() {

    glow::debug("Create WorldObjects");

    Ship *playerShip = WorldObjectBuilder("mox").buildShip();
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    playerShip->info().setName("basicship");
    playerShip->info().setShowOnHud(false);
    playerShip->info().setCanLockOn(false);

    m_world->god().scheduleSpawn(playerShip);
    World::instance()->player().setShip(playerShip);

    // create enemy ai driven ship
    Ship *aitester = WorldObjectBuilder("basicship").buildShip();
    aitester->transform().setPosition(glm::vec3(0, 0, 10));

    aitester->info().setName("basicship");
    aitester->info().setShowOnHud(false);
    aitester->character()->setTask(std::make_shared<FightTask>(aitester->boardComputer(), std::vector<Handle<WorldObject>>{ playerShip->handle<WorldObject>() }));

    //m_world->god().scheduleSpawn(aitester);


    WorldObject* banner = WorldObjectBuilder("banner").buildWorldObject();
    banner->transform().setScale(30.0f);
    banner->transform().move(glm::vec3(0, 0, -600));
    banner->info().setShowOnHud(false);
    banner->info().setCanLockOn(false);
    m_world->god().scheduleSpawn(banner);

    // create two opposing enemy forces
    populateBattle(3, 3);

    glow::debug("Initial spawn");
    m_world->god().spawn();
}

void BattleScenario::populateBattle(int numberOfEnemies1, int numberOfEnemies2) {
    std::vector<Ship*> fleet1;
    std::vector<Ship*> fleet2;
    for (int e = 0; e < numberOfEnemies1; e++) {
        Ship *ship = WorldObjectBuilder("basicship").buildShip();
        float r = 600;
        ship->transform().move(RandVec3::rand(0.0f, r) + glm::vec3(-200, 0, -200));

        ship->info().setName("enemy2");
        ship->info().setShowOnHud(true);
        ship->info().setCanLockOn(true);

        m_world->god().scheduleSpawn(ship);
        fleet2.push_back(ship);
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *ship = WorldObjectBuilder("basicship").buildShip();
        float r = 600;
        ship->transform().move(RandVec3::rand(0.0f, r) + glm::vec3(200, 0, -200));
        ship->info().setName("enemy1");
        ship->info().setShowOnHud(true);

        m_world->god().scheduleSpawn(ship);
        fleet1.push_back(ship);
    }

    spawnCapital(fleet1);

    setTargets(fleet1, fleet2);
    setTargets(fleet2, fleet1);
}

void BattleScenario::spawnCapital(const std::vector<Ship*>& enemies) {
    Ship *ship = WorldObjectBuilder("normandy").buildShip();
    ship->info().setShowOnHud(true);
    ship->info().setCanLockOn(true);

    ship->transform().move(glm::vec3(-200, 300, -200));

    std::vector<Handle<WorldObject>> enemyHandles;
    for (Ship* enemy : enemies) {
        Handle<WorldObject> handle = enemy->handle<WorldObject>();
        enemyHandles.push_back(handle);
    }
    ship->character()->setTask(std::make_shared<FightTask>(ship->boardComputer(), enemyHandles));
    m_world->god().scheduleSpawn(ship);
}

void BattleScenario::setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies) {
    std::vector<Handle<WorldObject>> enemyHandles;
    for (Ship* enemy : enemies) {
        enemyHandles.push_back(enemy->handle<WorldObject>());
    }
    enemyHandles.push_back(World::instance()->player().ship()->handle<WorldObject>());
    for (Ship* ship : fleet) {
        std::random_shuffle(enemyHandles.begin(), enemyHandles.end());
        ship->character()->setTask(std::make_shared<FightTask>(ship->boardComputer(), enemyHandles));
    }
}

