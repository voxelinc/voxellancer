#pragma once

#include <set>
#include <list>

#include "voxelimpact.h"

class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<VoxelImpact> &voxelImpacts);

    std::list<VoxelImpact> &deadlyVoxelImpacts();    
    std::set<WorldObject*> &modifiedVoxelClusters();


protected:
    std::list<VoxelImpact> m_deadlyVoxelImpacts;
    std::set<WorldObject*> m_modifiedVoxelClusters;

    float damageOfImpact(const Impact &impact) const;
};

