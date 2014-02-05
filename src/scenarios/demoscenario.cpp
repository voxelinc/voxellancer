#include "demoscenario.h"

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "ai/characters/dummycharacter.h"
#include "ai/elevatedtasks/dummyelevatedtask.h"
#include "ai/basictask.h"
#include "ai/basictasks/fighttask.h"
#include "ai/basictasks/flytotask.h"
#include "ai/elevatedtasks/patrolwaypointstask.h"

#include "resource/clustercache.h"

#include "worldobject/ship.h"

#include "game.h"
#include "world/world.h"
#include "world/god.h"
#include "utils/randvec.h"
#include "sound/soundmanager.h"

#include "GLFW/glfw3.h"

DemoScenario::DemoScenario(Game* game) :
BaseScenario(game) {
}

void DemoScenario::populateWorld() {

    Ship *playerShip = new Ship();
    ClusterCache::instance()->fillObject(playerShip, "data/voxelcluster/basicship.csv");
    playerShip->setPosition(glm::vec3(0, 0, 10));
    playerShip->objectInfo().setName("basicship");
    playerShip->objectInfo().setShowOnHud(false);
    m_world->god().scheduleSpawn(playerShip);

    m_game->player().setShip(playerShip);

    WorldObject *wall = new WorldObject();
    wall->move(glm::vec3(-30, 0, 50));
    wall->rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 15; y++) {
            for (int z = 0; z < 3; z++) {
                wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
            }
        }
    }
    wall->objectInfo().setName("Wall");
    wall->objectInfo().setShowOnHud(true);
    wall->objectInfo().setCanLockOn(true);
    m_world->god().scheduleSpawn(wall);

    createPlanet(glm::vec3(100, 0, -40), 24, 0x0000AA);

    populateBattle(5, 5);

    m_world->god().spawn();
}

void DemoScenario::createDummyTarget(glm::vec3 positionToPlayer) {
    WorldObject *target = new WorldObject();
    target->move(m_game->player().playerShip()->transform().applyTo(positionToPlayer));

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 5; z++) {
                target->addVoxel(new Voxel(glm::ivec3(x, y, z), 0xF0FF00));
            }
        }
    }
    target->objectInfo().setName("dummy Target");
    target->objectInfo().setShowOnHud(true);
    target->objectInfo().setCanLockOn(false);
    m_world->god().scheduleSpawn(target);
}

void DemoScenario::createSingleEnemy(glm::vec3 positionToPlayer) {
    Ship *target = new Ship();
    ClusterCache::instance()->fillObject(target, "data/voxelcluster/basicship.csv");
    target->setPosition(m_game->player().playerShip()->transform().applyTo(positionToPlayer));
    target->rotate(glm::angleAxis(glm::radians(180.0f), glm::vec3(0, 1, 0)));
    target->objectInfo().setName("enemy");
    target->objectInfo().setShowOnHud(true);
    target->objectInfo().setCanLockOn(true);
    target->setCharacter(new DummyCharacter(*target, new DummyElevatedTask(*target, new FightTask(*target, {m_game->player().playerShip()->handle()}))));
    m_world->god().scheduleSpawn(target);
    m_game->player().playerShip()->setTargetObject(target);
}

void DemoScenario::callInNormandy(glm::vec3 positionToPlayer) {
    Ship *target = new Ship();
    ClusterCache::instance()->fillObject(target, "data/voxelcluster/normandy.csv");
    target->setPosition(m_game->player().playerShip()->transform().applyTo(positionToPlayer));
    target->objectInfo().setName("normandy");
    target->objectInfo().setShowOnHud(true);
    target->objectInfo().setCanLockOn(true);
    target->setCharacter(new DummyCharacter(*target, new DummyElevatedTask(*target, new FightTask(*target, nonNormandies()))));
    m_world->god().scheduleSpawn(target);
}

void DemoScenario::onKeyPressed(int key) {
    switch (key) {
        case GLFW_KEY_F1:
            createDummyTarget(glm::vec3(0, 5, -80));
            break;
        case GLFW_KEY_F2:
            createSingleEnemy(glm::vec3(0, 5, -500));
            break;
        case GLFW_KEY_F3:
            startBattle();
            break;
        case GLFW_KEY_F4:
            endBattle();
            break; 
        case GLFW_KEY_F7:
            callInNormandy(glm::vec3(0, 0, 200));
            callInNormandy(glm::vec3(150, 0, 200));
            callInNormandy(glm::vec3(-150, 0, 200));
            break;
        case GLFW_KEY_F8:
            turnBattleOnPlayer();
            break
        default:
            break;
    }
}

void DemoScenario::populateBattle(int numberOfEnemies1, int numberOfEnemies2) {
    World* world = World::instance();
    for (int e = 0; e < numberOfEnemies1; e++) {
        Ship *ship = new Ship();
        float r = numberOfEnemies1 * 50.0f;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(-400, 0, -800));
        ship->objectInfo().setName("enemy1");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        ClusterCache::instance()->fillObject(ship, "data/voxelcluster/eagle.csv");
        world->god().scheduleSpawn(ship);
        m_fleet1.push_back(ship->handle());
    }
    for (int e = 0; e < numberOfEnemies2; e++) {
        Ship *ship = new Ship();
        float r = numberOfEnemies2 * 50.0f;
        ship->move(RandVec3::rand(0.0f, r) + glm::vec3(400, 0, -800));
        ship->objectInfo().setName("enemy2");
        ship->objectInfo().setShowOnHud(true);
        ship->objectInfo().setCanLockOn(true);
        ClusterCache::instance()->fillObject(ship, "data/voxelcluster/eagle.csv");
        world->god().scheduleSpawn(ship);
        m_fleet2.push_back(ship->handle());
    }
}

void DemoScenario::startBattle() {
    setTargets(m_fleet1, m_fleet2);
    setTargets(m_fleet2, m_fleet1);
}

void DemoScenario::endBattle() {
    setTargets(m_fleet1, std::vector<Handle<WorldObject>>{});
    setTargets(m_fleet2, std::vector<Handle<WorldObject>>{});
}

void DemoScenario::turnBattleOnPlayer() {
    setTargets(m_fleet1, std::vector<Handle<WorldObject>>{m_game->player().playerShip()->handle()});
    setTargets(m_fleet2, std::vector<Handle<WorldObject>>{m_game->player().playerShip()->handle()});
    for (Handle<WorldObject> enemy : m_fleet1) {
        if (enemy.valid()) {
            enemy.get()->objectInfo().setShowOnHud(true);
            enemy.get()->objectInfo().setCanLockOn(true);
        }
    }
    for (Handle<WorldObject> enemy : m_fleet2) {
        if (enemy.valid()) {
            enemy.get()->objectInfo().setShowOnHud(true);
            enemy.get()->objectInfo().setCanLockOn(true);
        }
    }
}

void DemoScenario::setTargets(const std::vector<Handle<WorldObject>>& fleet, const std::vector<Handle<WorldObject>>& enemies) {
    std::vector<Handle<WorldObject>> enemyHandles;
    for (Handle<WorldObject> enemy : enemies) {
        if (enemy.get()) {
            enemyHandles.push_back(enemy);
        }
    }
    for (Handle<WorldObject> shipHandle : fleet) {
        if (shipHandle.valid()) {
            Ship* ship = dynamic_cast<Ship*>(shipHandle.get());
            if (ship) {
                std::random_shuffle(enemyHandles.begin(), enemyHandles.end());
                ship->setCharacter(new DummyCharacter(*ship, new DummyElevatedTask(*ship, new FightTask(*ship, enemyHandles))));
            }
        }
    }
}

std::vector<Handle<WorldObject>> DemoScenario::nonNormandies() {
    std::vector<Handle<WorldObject>> result;
    for (Handle<WorldObject>& handle : m_fleet1) {
        if (handle.valid()) {
            result.push_back(handle);
        }
    }
    for (Handle<WorldObject>& handle : m_fleet2) {
        if (handle.valid()) {
            result.push_back(handle);
        }
    }
    return result;
}