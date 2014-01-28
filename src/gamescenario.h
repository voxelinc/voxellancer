#pragma once

#include <memory>

#include "worldobject/worldobjecthandle.h"

class Game;
class Ship;

class GameScenario {
public:
    GameScenario();

    void populate(Game* game);
    void update(float deltaSec);


protected:
    std::shared_ptr<WorldObjectHandle> m_normandy;
    std::shared_ptr<WorldObjectHandle> m_aimTester;
};

