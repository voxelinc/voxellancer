#pragma once

#include "voxel/voxelcluster.h"


class MassBalancer
{
public:
    MassBalancer(VoxelCluster &voxelcluster);

    void adjustCenterOfMass();


protected:
    VoxelCluster &m_voxelcluster;
};
