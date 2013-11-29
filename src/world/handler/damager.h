#pragma once

#include <set>
#include <list>

#include "physics/physicalvoxelimpact.h"


class WorldObject;

class Damager
{
public:
    void applyDamages(std::list<PhysicalVoxelImpact> &voxelImpacts);

    std::list<PhysicalVoxelImpact> &deadlyVoxelImpacts();
    std::set<WorldObject*> &modifiedVoxelClusters();


protected:
    std::list<PhysicalVoxelImpact> m_deadlyVoxelImpacts;
    std::set<WorldObject*> m_modifiedVoxelClusters;

    float damageOfImpact(const Impact &impact) const;
};

