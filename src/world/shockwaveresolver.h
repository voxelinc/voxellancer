#pragma once

#include "physics/shockwave.h"

#include "god.h"



class ShockwaveResolver
{
public:
    ShockwaveResolver(God &god);
    virtual ~ShockwaveResolver();

    void resolve(std::list<Shockwave*> &shockwaves);

    std::list<VoxelImpact*> &voxelImpacts();
};

