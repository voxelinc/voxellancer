#pragma once

#include "voxel/voxel.h"
#include "physics/impact.h"


class VoxelImpact
{
public:
    VoxelImpact(Voxel *voxel, const Impact &impact);

    Voxel *voxel();
    const Voxel *voxel() const;

    const Impact &impact() const;

    void addImpact(const Impact &impact);


protected:
    Voxel *m_voxel;
    Impact m_impact;
};

