#pragma once

#include "scenarios/basescenario.h"

class GamePlay;

class TransparencyScenario : public BaseScenario {
public:
    TransparencyScenario(GamePlay* inGame);

protected:
    virtual void populateWorld() override;
};

