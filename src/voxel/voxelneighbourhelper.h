#pragma once

#include <list>

#include "voxel.h"

class VoxelCluster;

class VoxelNeighbourHelper
{
public:
    VoxelNeighbourHelper(VoxelCluster *voxelCluster, Voxel *voxel, bool includeDiagonals = false);

    std::list<Voxel*> neighbours();


protected:
    Voxel *m_voxel;
    VoxelCluster *m_voxelCluster;
    bool m_includeDiagonals;
    std::list<Voxel*> m_neighbours;

    void considerNeighbour(const glm::ivec3 &relativeCell);
};
