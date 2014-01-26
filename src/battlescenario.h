#pragma once


class Game;

class BattleScenario {
public:
    BattleScenario();

    void populate(Game* game);

private:
    void populateBattle(int numberOfEnemies1, int numberOfEnemies2);
};