#pragma once

#include "voxel/voxel.h"

class HardpointVoxel : public Voxel {
public:
    HardpointVoxel();
    HardpointVoxel(cvec3 gridCell, cvec3 color);
    ~HardpointVoxel();

    virtual void addToCluster(VoxelCluster *cluster);
};