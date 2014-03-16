#pragma once

#include "scenarios/basescenario.h"

class GamePlay;

class PirateScenario : public BaseScenario {
public:
    PirateScenario(GamePlay* inGame);

protected:
    virtual void populateWorld() override;

    void createArmada();
};

