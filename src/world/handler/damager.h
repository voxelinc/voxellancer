#pragma once

#include <list>

#include "voxelimpact.h"

class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &deadlyVoxelImpacts();
    std::list<WorldObject*> &modifiedVoxelClusters();

protected:
    std::list<VoxelImpact> m_deadlyVoxelImpacts;
    std::list<WorldObject*> m_modifiedVoxelClusters;
};

