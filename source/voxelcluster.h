#pragma once

#include "geometry/aabb.h"

class Voxelcluster
{
public:
    Voxelcluster();
    virtual ~Voxelcluster();

    const AABB &aabb();

protected:
    AABB m_aabb;
};
