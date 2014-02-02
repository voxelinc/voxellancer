#include "battlescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/fighttask.h"

#include "resource/clustercache.h"
#include "resource/worldobjectfactory.h"

#include "worldobject/ship.h"

#include "game.h"
#include "world/world.h"
#include "world/god.h"
#include "utils/randvec.h"


BattleScenario::BattleScenario() {

}

void BattleScenario::populate(Game* game) {
    glowutils::AutoTimer t("Initialize Game");

    glow::debug("create world");
    World* world = World::instance();

    glow::debug("Create WorldObjects");

    // create playership
    Ship *playerShip = WorldObjectFactory<Ship>("basicship");
    playerShip->setPosition(glm::vec3(0, 0, 10));
    world->god().scheduleSpawn(playerShip);
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
        Ship *ship = WorldObjectFactory<Ship>("basicship");
        float r = 200;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(-200, 0, -200));
        ship->objectInfo().setName("enemy2");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        world->god().scheduleSpawn(ship);
        fleet2.push_back(ship);
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *ship  = WorldObjectFactory<Ship>("basicship");
        float r = 200;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(200, 0, -200));
        ship->objectInfo().setName("enemy1");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        world->god().scheduleSpawn(ship);
        fleet1.push_back(ship);
    }
    setTargets(fleet1, fleet2);
    setTargets(fleet2, fleet1);
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
