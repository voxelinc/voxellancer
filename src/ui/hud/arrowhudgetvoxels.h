#pragma once

#include <vector>

#include "voxel/voxelcluster.h"
#include "property/property.h"

class ArrowHudget;

class ArrowHudgetVoxels {
public:
    ArrowHudgetVoxels(ArrowHudget* hudget);
    ~ArrowHudgetVoxels();

    ArrowHudget* hudget();

    void draw();

    void setTarget(bool target);


protected:
    ArrowHudget* m_hudget;
    VoxelCluster m_arrow;

    Property<float> prop_arrowDistance;

    glm::vec3 m_targetPoint;

    bool findPoint();


};

