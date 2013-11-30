#pragma once

#include "voxel/voxel.h"

class CockpitVoxel : public Voxel {
public:
    CockpitVoxel();
    CockpitVoxel(cvec3 gridCell, cvec3 color);
    ~CockpitVoxel();

    virtual void addToCluster(VoxelCluster *cluster);
};