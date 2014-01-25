#pragma once

#include <vector>

#include "voxel/voxelcluster.h"


class ObjectDelegateHudget;
class ObjectDelegateHudgetVoxels;

class ObjectDelegateHudgetVoxels {
public:
    ObjectDelegateHudgetVoxels(ObjectDelegateHudget* hudget);
    ~ObjectDelegateHudgetVoxels();

    void setEdgeLength(float edgeLength);

    void draw();


protected:
    ObjectDelegateHudget* m_hudget;
    VoxelCluster* m_lu;
    VoxelCluster* m_lb;
    VoxelCluster* m_ru;
    VoxelCluster* m_rb;
    float m_edgeLength;

    void setupCorners();
};

