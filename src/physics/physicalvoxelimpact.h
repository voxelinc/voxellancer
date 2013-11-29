#pragma once

#include "physics/impact.h"


class PhysicalVoxel;

class PhysicalVoxelImpact
{
public:
    PhysicalVoxelImpact(PhysicalVoxel *physicalVoxel, const Impact &impact);

    PhysicalVoxel *physicalVoxel();
    const PhysicalVoxel *physicalVoxel() const;

    const Impact &impact() const;

    void addImpact(const Impact &impact);


protected:
    PhysicalVoxel *m_physicalVoxel;
    Impact m_impact;
};

