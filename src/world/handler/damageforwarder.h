#pragma once

#include <list>


#include "world/helper/damageimpact.h"
#include "world/helper/voxelaccumulator.h"


class DamageForwarder
{
public:
    void forwardDamageImpacts(std::list<DamageImpact> &dampedDeadlyDamageImpacts);
    void dontForwardTo(std::list<Voxel*> &deadVoxels);

    std::list<DamageImpact> forwardedDamageImpacts();


protected:
    WorldObject *m_currentWorldObject;
    std::list<Voxel*> *m_currentNeighbours;
    glm::ivec3 m_currentGridCell;

    VoxelAccumulator<DamageImpact> m_damageImpactAccumulator;

    float forwardFactor(float dotProduct);
};

