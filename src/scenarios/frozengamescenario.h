#pragma once

#include "scenarios/basescenario.h"

class GamePlay;

class FrozenGameScenario : public BaseScenario {
public:
    FrozenGameScenario(GamePlay* inGame);

protected:
    virtual void populateWorld() override;
};

