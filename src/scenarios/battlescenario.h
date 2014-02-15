#pragma once

#include <vector>

#include "basescenario.h"

class GamePlay;
class Ship;

class BattleScenario: public BaseScenario {
public:
    BattleScenario(GamePlay* gamePlay);

private:
    virtual void populateWorld() override;
    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);
    void setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies);

};
