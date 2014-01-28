#pragma once

#include "voxel/voxelcluster.h"


class TargetGuideArrow;

class TargetGuideArrowVoxels: public VoxelCluster {
public:
    TargetGuideArrowVoxels(TargetGuideArrow* arrow);

    void draw();

protected:
    TargetGuideArrow* m_arrow;
};
