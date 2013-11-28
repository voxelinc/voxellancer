#pragma once

#include <list>

#include "voxelimpact.h"


class DamageForwarder
{
public:
    void forwardDamage(std::list<VoxelImpact> &deadlyVoxelImpacts);
    std::list<VoxelImpact> &forwardedDamageImpacts();


protected:
    std::list<VoxelImpact> m_forwardedDamageImpacts;
};

