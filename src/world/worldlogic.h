#pragma once

#include "mover.h"
#include "mover.h"


class World;

class WorldLogic
{
public:
    WorldLogic(World &world);

    void update();


protected:
    World &m_world;
    Mover m_mover;
    std::list<VoxelClusterImpact> m_;
};
