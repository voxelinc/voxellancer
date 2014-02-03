#pragma once

#include <memory>

#include "worldobject/handle/handle.h"


class Game;
class Ship;

class GameScenario {
public:
    GameScenario();

    void populate(Game* game);
    void update(float deltaSec);


protected:
    Handle<Ship> m_normandy;
    Handle<Ship> m_aimTester;
};

