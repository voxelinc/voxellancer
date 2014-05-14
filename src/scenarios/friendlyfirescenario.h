#pragma once

#include "scenarios/basescenario.h"

class GamePlay;

class FriendlyFireScenario : public BaseScenario {
public:
    FriendlyFireScenario(GamePlay* inGame);

protected:
    virtual void populateWorld() override;
};

