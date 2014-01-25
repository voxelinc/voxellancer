#pragma once

#include <vector>

#include "voxel/voxelcluster.h"


class ObjectHudget;

class ObjectHudgetVoxels {
public:
    ObjectHudgetVoxels(ObjectHudget* hudget);
    ~ObjectHudgetVoxels();

    void setEdgeLength(float edgeLength);

    void draw();


protected:
    ObjectHudget* m_hudget;
    VoxelCluster* m_lu;
    VoxelCluster* m_lb;
    VoxelCluster* m_ru;
    VoxelCluster* m_rb;
    float m_edgeLength;

    void setupCorners();
};

