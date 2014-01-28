#pragma once


#include "game.h"

class BaseScenario {
public:
    BaseScenario(Game* game);

    virtual void load();
    virtual void reset();

protected:
    Game* m_game;
    World* m_world;

    virtual void createWorld();
    virtual void populateWorld();
    virtual void clear();
};

