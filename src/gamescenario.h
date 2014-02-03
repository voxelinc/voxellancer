#pragma once

#include <memory>

#include "worldobject/ship.h"
#include "worldobject/worldobject.h"
#include "worldobject/handle/handle.h"


class Game;
class Ship;

class GameScenario {
public:
    GameScenario();

    void populate(Game* game);
};

