#pragma once

#include "scenarios/basescenario.h"

class Game;

class FrozenGameScenario : public BaseScenario {
public:
    FrozenGameScenario(Game* game);

protected:
    virtual void populateWorld() override;
};

