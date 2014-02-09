#pragma once

#include <vector>

#include "voxel/voxelcluster.h"

class ArrowHudget;

class ArrowHudgetVoxels {
public:
    ArrowHudgetVoxels(ArrowHudget* hudget);
    ~ArrowHudgetVoxels();

    ArrowHudget* hudget();

    void draw();


protected:
    ArrowHudget* m_hudget;
    VoxelCluster m_arrow;

    float m_angleX, m_angleY;
    glm::vec3 m_targetPoint;

    void calculateAngles();


};

