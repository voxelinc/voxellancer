#pragma once

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"

class ObjectHudgetVoxels;


class ObjectHudgetCornerVoxels: public VoxelCluster {
public:
    ObjectHudgetCornerVoxels(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset, uint32_t baseColor, bool targetHightlight);

    void draw();


protected:
    ObjectHudgetVoxels* m_objectHudgetVoxels;
    glm::ivec3 m_baseOffset;
};

