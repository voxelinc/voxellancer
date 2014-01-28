#pragma once

#include "scenarios/basescenario.h"

class Game;

class GameScenario : public BaseScenario {
public:
    GameScenario(Game* game);

protected:
    virtual void populateWorld();
};

