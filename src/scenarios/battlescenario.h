#pragma once

#include <vector>

#include "scenarios/basescenario.h"

class Game;
class Ship;

class BattleScenario : public BaseScenario {
public:
    BattleScenario(Game* game);

protected:
    virtual void populateWorld() override;

private:
    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);

    void setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies);
};