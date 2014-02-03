#include "battlescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/fighttask.h"

#include "resource/clustercache.h"
#include "resource/worldobjectfactory.h"

#include "worldobject/components/hardpoint.h"
#include "worldobject/components/engineslot.h"
#include "worldobject/components/engine.h"
#include "worldobject/components/weapon.h"
#include "worldobject/components/weapons/gun.h"
#include "worldobject/components/engines/piratethruster.h"
#include "worldobject/ship.h"

#include "world/world.h"
#include "world/god.h"

#include "game.h"
#include "utils/randvec.h"




BattleScenario::BattleScenario() {

}

void BattleScenario::populate(Game* game) {
    glowutils::AutoTimer t("Initialize Game");

    glow::debug("create world");
    World* world = World::instance();

    glow::debug("Create WorldObjects");

    // create playership

    Ship *playerShip = WorldObjectFactory().build<Ship>("basicship");
    playerShip->transform().setPosition(glm::vec3(0, 0, 10));
    world->god().scheduleSpawn(playerShip);
    playerShip->components().hardpoint(0)->setWeapon(new Gun());
    playerShip->components().hardpoint(1)->setWeapon(new Gun());
    playerShip->components().engineSlot(0)->setEngine(new PirateThruster());
    game->player().setShip(playerShip);

    populateBattle(4, 4);

    glow::debug("Initial spawn");
    world->god().spawn();
}

void BattleScenario::populateBattle(int numberOfEnemies1, int numberOfEnemies2) {
    World* world = World::instance();
    std::vector<Ship*> fleet1;
    std::vector<Ship*> fleet2;
    for (int e = 0; e < numberOfEnemies1; e++) {

        Ship *ship = WorldObjectFactory().build<Ship>("basicship");
        WorldObjectFactory().equipSomehow(ship);

        float r = 200;
        ship->transform().move(RandVec3::rand(0.0f, r) + glm::vec3(-200, 0, -200));
        ship->objectInfo().setName("enemy2");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);

        world->god().scheduleSpawn(ship);
        fleet2.push_back(ship);
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *ship  = WorldObjectFactory().build<Ship>("basicship");
        WorldObjectFactory().equipSomehow(ship);


        float r = 200;
        ship->transform().move(RandVec3::rand(0.0f, r) + glm::vec3(200, 0, -200));
        ship->objectInfo().setName("enemy1");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);

        world->god().scheduleSpawn(ship);
        fleet1.push_back(ship);
    }

    spawnCapital(fleet1);

    setTargets(fleet1, fleet2);
    setTargets(fleet2, fleet1);
}

void BattleScenario::spawnCapital(const std::vector<Ship*>& enemies) {
    Ship *ship  = WorldObjectFactory().build<Ship>("normandy");
    WorldObjectFactory().equipSomehow(ship);
    ship->transform().move(glm::vec3(-200, 300, -200));

    std::vector<Handle<WorldObject>> enemyHandles;
    for (Ship* enemy : enemies) {
        enemyHandles.push_back(enemy->handle());
    }
    ship->setCharacter(new DummyCharacter(*ship, new DummyElevatedTask(*ship, new FightTask(*ship, enemyHandles))));
    World::instance()->god().scheduleSpawn(ship);
}

void BattleScenario::setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies) {
    std::vector<Handle<WorldObject>> enemyHandles;
    for (Ship* enemy : enemies) {
        enemyHandles.push_back(enemy->handle());
    }
    for (Ship* ship : fleet) {
        std::random_shuffle(enemyHandles.begin(), enemyHandles.end());
        ship->setCharacter(new DummyCharacter(*ship, new DummyElevatedTask(*ship, new FightTask(*ship, enemyHandles))));
    }
}
