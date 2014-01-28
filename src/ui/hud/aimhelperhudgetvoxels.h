#pragma once

#include "voxel/voxelcluster.h"


class AimHelperHudget;

class AimHelperHudgetVoxels {
public:
    AimHelperHudgetVoxels(AimHelperHudget* aimHelperHudget);

    void draw();


protected:
    AimHelperHudget* m_aimHelperHudget;
    VoxelCluster m_dot;
    VoxelCluster m_circle;
};

