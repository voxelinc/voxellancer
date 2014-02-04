#pragma once

#include <vector>

#include "scenarios/basescenario.h"

class Game;
class Ship;

class DemoScenario : public BaseScenario {
public:
    DemoScenario(Game* game);

    virtual void onKeyPressed(int key) override;


protected:
    virtual void populateWorld() override;

private:

    std::vector<Ship*> m_fleet1;
    std::vector<Ship*> m_fleet2;

    void createDummyTarget(glm::vec3 positionToPlayer);
    void createSingleEnemy(glm::vec3 positionToPlayer);

    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);

    void startBattle();
    void endBattle();
    void turnBattleOnPlayer();
    void setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies);

};