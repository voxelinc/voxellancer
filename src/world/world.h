#pragma once

#include "worldtree/worldtree.h"


class World
{
public:
    World();
    virtual ~World();

    void update();


protected:
    Worldtree m_worldtree;
    WorldLogic m_logic;
    God m_god;
};

