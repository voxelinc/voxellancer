#pragma once

#include "voxel/voxel.h"

class EngineVoxel : public Voxel {
public:
    EngineVoxel();
    EngineVoxel(cvec3 gridCell, cvec3 color);
    ~EngineVoxel();

    virtual void addToCluster(VoxelCluster *cluster);
};