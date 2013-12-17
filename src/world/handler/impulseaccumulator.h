#pragma once

#include <set>
#include <list>
#include <map>

#include "collision/voxelcollision.h"
#include "collision/worldobjectcollision.h"

#include "physics/impulse.h"


class Voxel;

class ImpulseAccumulator
{
public:
    void clear();

    void parse(const std::list<Impulse> &impulses);

    void dontImpulse(const std::list<Voxel*> voxels);

    std::list<Impulse>& impulses();


protected:
    std::map<const Voxel*, Impulse> m_voxelImpulseMap;
    std::list<Impulse> m_impulses;

    void parseCollision(WorldObject *worldObject, const VoxelCollision& collision);
};

