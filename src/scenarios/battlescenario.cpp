#include "battlescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/character.h"
#include "ai/basictasks/fighttask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"

#include "game.h"
#include "world/world.h"
#include "world/god.h"
#include "utils/randvec.h"


BattleScenario::BattleScenario(Game* game):
    BaseScenario(game)
{

}

void BattleScenario::populateWorld() {
    glowutils::AutoTimer t("Initialize Game");


    glow::debug("create world");
    World* world = World::instance();

    glow::debug("Create WorldObjects");

    // create playership
    Ship *playerShip = new Ship();
    ClusterCache::instance()->fillObject(playerShip, "data/voxelcluster/basicship.csv");
    playerShip->setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    playerShip->objectInfo().setCanLockOn(false);
    world->god().scheduleSpawn(playerShip);
    m_game->player().setShip(playerShip);

    // create enemy ai driven ship
    Ship *aitester = new Ship();
    ClusterCache::instance()->fillObject(aitester, "data/voxelcluster/basicship.csv");
    aitester->setPosition(glm::vec3(0, 0, 10));
    aitester->objectInfo().setName("basicship");
    aitester->objectInfo().setShowOnHud(false);
    aitester->character()->setTask(std::make_shared<FightTask>(*aitester, std::vector<Handle<WorldObject>>{ playerShip->handle() }));
    //world->god().scheduleSpawn(aitester);

    WorldObject* banner = new WorldObject();
    ClusterCache::instance()->fillObject(banner, "data/voxelcluster/banner.csv");
    banner->transform().setScale(30.0f);
    banner->transform().move(glm::vec3(0, 0, -600));
    banner->objectInfo().setShowOnHud(false);
    banner->objectInfo().setCanLockOn(false);
    world->god().scheduleSpawn(banner);

    // create two opposing enemy forces
    populateBattle(3, 3);

    glow::debug("Initial spawn");
    world->god().spawn();
}

void BattleScenario::populateBattle(int numberOfEnemies1, int numberOfEnemies2) {
    World* world = World::instance();
    std::vector<Ship*> fleet1;
    std::vector<Ship*> fleet2;
    for (int e = 0; e < numberOfEnemies1; e++) {
        Ship *ship = new Ship();
        float r = 600;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(-200, 0, -200));
        ship->objectInfo().setName("enemy2");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        ClusterCache::instance()->fillObject(ship, "data/voxelcluster/basicship.csv");
        world->god().scheduleSpawn(ship);
        fleet2.push_back(ship);
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *ship = new Ship();
        float r = 600;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(200, 0, -200));
        ship->objectInfo().setName("enemy1");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        ClusterCache::instance()->fillObject(ship, "data/voxelcluster/unogunner.csv");
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
        ship->character()->setTask(std::make_shared<FightTask>(*ship, enemyHandles));
    }
}
