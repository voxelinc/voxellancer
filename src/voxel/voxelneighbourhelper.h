#pragma once

#include <list>

#include "voxel.h"

class VoxelCluster;

class VoxelNeighbourHelper
{
public:
    VoxelNeighbourHelper(VoxelCluster *voxelCluster, bool includeDiagonals = true);

    const std::vector<Voxel*>& neighbours(const glm::ivec3& pos);
    const std::vector<Voxel*>& neighbours(const Voxel* voxel);

protected:
    VoxelCluster *m_voxelCluster;
    std::vector<Voxel*> m_neighbours;
    bool m_includeDiagonals;

    void considerNeighbour(const glm::ivec3& pos, const glm::ivec3& offset);
};
