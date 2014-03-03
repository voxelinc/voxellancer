#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "voxel/voxelcluster.h"


class ObjectHudgetVoxels;

class ObjectHudgetCornerVoxels {
public:
    ObjectHudgetCornerVoxels(ObjectHudgetVoxels* objectHudgetVoxels, const glm::ivec3& baseOffset);

    const glm::vec3& position() const;
    const glm::quat& orientation() const;

    void update(float deltaSec);
    void draw(int index);


protected:
    ObjectHudgetVoxels* m_objectHudgetVoxels;
    glm::ivec3 m_baseOffset;

    glm::vec3 m_position;
    glm::quat m_orientation;

    std::vector<std::unique_ptr<VoxelCluster>> m_voxelClusters;

    void addIndex(int index, uint32_t color, float scale);
};

