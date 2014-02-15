#pragma once

#include <vector>

class GamePlay;
class Ship;

class BattleScenario {
public:
    BattleScenario();

    void populate(GamePlay* inGame);


private:
    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);
    void setTargets(const std::vector<Ship*>& fleet, const std::vector<Ship*>& enemies);

};

