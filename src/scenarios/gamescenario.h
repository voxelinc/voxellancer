#pragma once

#include "scenarios/basescenario.h"

class InGame;

class GameScenario : public BaseScenario {
public:
    GameScenario(InGame* inGame);

protected:
    virtual void populateWorld() override;
};

