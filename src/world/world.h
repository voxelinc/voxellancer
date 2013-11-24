#pragma once

#include "worldtree/worldtree.h"

#include "worldlogic.h"


class World
{
public:
    World();
    virtual ~World();

    WorldLogic &worldLogic();
    God &god();
    Worldtree &worldtree();

    float deltaSecs() const;

    void update(float deltaSecs);

    static World *instance();

protected:
    static World *s_instance;

    Worldtree m_worldtree;
    WorldLogic m_worldLogic;
    God m_god;
    float m_deltaSecs;
};

