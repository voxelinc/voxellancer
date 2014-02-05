#pragma once

#include <vector>

#include "scenarios/basescenario.h"
#include "worldobject/handle/handle.h"

class Game;
class Ship;

class DemoScenario : public BaseScenario {
public:
    DemoScenario(Game* game);

    virtual void onKeyPressed(int key) override;


protected:
    virtual void populateWorld() override;

private:

    std::vector<Handle<WorldObject>> m_fleet1;
    std::vector<Handle<WorldObject>> m_fleet2;

    void callInNormandy(glm::vec3 positionToPlayer);
    void createDummyTarget(glm::vec3 positionToPlayer);
    void createSingleEnemy(glm::vec3 positionToPlayer);

    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);

    void startBattle();
    void endBattle();
    void turnBattleOnPlayer();
    void setTargets(const std::vector<Handle<WorldObject>>& fleet, const std::vector<Handle<WorldObject>>& enemies);

    std::vector<Handle<WorldObject>> nonNormandies();
};