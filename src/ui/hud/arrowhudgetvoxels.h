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

    glm::vec3 m_targetPoint;
    float angleToPlane(glm::vec3 planeNormal);

    void calculateAngles();


};

