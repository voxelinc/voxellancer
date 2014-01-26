#include "battlescenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/fight.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"

#include "game.h"


BattleScenario::BattleScenario() {

}

void BattleScenario::populate(Game* game) {
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
    world->god().scheduleSpawn(playerShip);
    game->player().setShip(playerShip);

    // create enemy ai driven ship
    Ship *aitester = new Ship();
    ClusterCache::instance()->fillObject(aitester, "data/voxelcluster/basicship.csv");
    aitester->setPosition(glm::vec3(0, 0, 10));
    aitester->objectInfo().setName("basicship");
    aitester->objectInfo().setShowOnHud(false);
    //world->god().scheduleSpawn(aitester);
    aitester->setCharacter(new DummyCharacter(*aitester, new DummyElevatedTask(*aitester, new Fight(*aitester, std::list<std::shared_ptr<WorldObjectHandle>>{playerShip->handle()}))));

    // create two opposing enemy forces
    populateBattle(10, 10);

    glow::debug("Initial spawn");
    world->god().spawn();
}

void BattleScenario::populateBattle(int numberOfEnemies1, int numberOfEnemies2) {
    World* world = World::instance();
    std::list<std::shared_ptr<WorldObjectHandle>> enemies1;
    std::list<std::shared_ptr<WorldObjectHandle>> enemies2;
    for (int e = 0; e < numberOfEnemies1; e++) {
        Ship *enemy = new Ship();
        int r = 200;
        enemy->move(glm::vec3(-200 + rand() % r - r / 2, rand() % r - r / 2, -200 + rand() % r - r / 2));
        enemy->objectInfo().setName("enemy2");
        enemy->objectInfo().setShowOnHud(false);
        enemy->objectInfo().setCanLockOn(false);
        ClusterCache::instance()->fillObject(enemy, "data/voxelcluster/basicship.csv");
        world->god().scheduleSpawn(enemy);
        enemies2.push_back(enemy->handle());
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *enemy = new Ship();
        int r = 200;
        enemy->move(glm::vec3(200 + rand() % r - r / 2, rand() % r - r / 2, -200 + rand() % r - r / 2));
        enemy->objectInfo().setName("enemy1");
        enemy->objectInfo().setShowOnHud(false);
        enemy->objectInfo().setCanLockOn(false);
        ClusterCache::instance()->fillObject(enemy, "data/voxelcluster/basicship.csv");
        world->god().scheduleSpawn(enemy);
        enemies1.push_back(enemy->handle());
    }
    for (std::shared_ptr<WorldObjectHandle> handle : enemies1) {

        std::vector<std::shared_ptr<WorldObjectHandle>> tmpVector(enemies2.size());
        std::copy(enemies2.begin(), enemies2.end(), tmpVector.begin());
        std::random_shuffle(tmpVector.begin(), tmpVector.end());
        copy(tmpVector.begin(), tmpVector.end(), enemies2.begin());

        Ship* e = (Ship*)handle->get();
        e->setCharacter(new DummyCharacter(*e, new DummyElevatedTask(*e, new Fight(*e, enemies2))));
    }
    for (std::shared_ptr<WorldObjectHandle> handle : enemies2) {
        std::vector<std::shared_ptr<WorldObjectHandle>> tmpVector(enemies1.size());
        std::copy(enemies1.begin(), enemies1.end(), tmpVector.begin());
        std::random_shuffle(tmpVector.begin(), tmpVector.end());
        copy(tmpVector.begin(), tmpVector.end(), enemies1.begin());

        Ship* e = (Ship*)handle->get();
        e->setCharacter(new DummyCharacter(*e, new DummyElevatedTask(*e, new Fight(*e, enemies1))));
    }
}