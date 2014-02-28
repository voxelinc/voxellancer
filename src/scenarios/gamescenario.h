#pragma once

#include "scenarios/basescenario.h"

class GamePlay;

class GameScenario : public BaseScenario {
public:
    GameScenario(GamePlay* inGame);

protected:
    virtual void populateWorld() override;

    void createArmada();
};

