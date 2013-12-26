#include "voxelneighbourhelper.h"

#include "geometry/grid3daabb.h"

#include "voxel/voxelcluster.h"


VoxelNeighbourHelper::VoxelNeighbourHelper(VoxelCluster *voxelCluster, bool includeDiagonals):
    m_voxelCluster(voxelCluster),
    m_includeDiagonals(includeDiagonals)
{
    assert(voxelCluster != nullptr);
}

const std::list<Voxel*>& VoxelNeighbourHelper::neighbours(const Voxel * voxel) {
    return neighbours(voxel->gridCell());
}


const std::list<Voxel*>& VoxelNeighbourHelper::neighbours(const glm::ivec3& pos) {
    m_neighbours.clear();

    considerNeighbour(pos, glm::ivec3(-1, 0, 0));
    considerNeighbour(pos, glm::ivec3(+1, 0, 0));
    considerNeighbour(pos, glm::ivec3(0, -1, 0));
    considerNeighbour(pos, glm::ivec3(0, +1, 0));
    considerNeighbour(pos, glm::ivec3(0, 0, -1));
    considerNeighbour(pos, glm::ivec3(0, 0, +1));

    if(m_includeDiagonals) {
        considerNeighbour(pos, glm::ivec3(-1, -1, 0));
        considerNeighbour(pos, glm::ivec3(-1, +1, 0));
        considerNeighbour(pos, glm::ivec3(+1, +1, 0));
        considerNeighbour(pos, glm::ivec3(+1, -1, 0));
        considerNeighbour(pos, glm::ivec3(-1, 0, -1));
        considerNeighbour(pos, glm::ivec3(-1, 0, +1));
        considerNeighbour(pos, glm::ivec3(+1, 0, +1));
        considerNeighbour(pos, glm::ivec3(+1, 0, -1));
        considerNeighbour(pos, glm::ivec3(0, -1, -1));
        considerNeighbour(pos, glm::ivec3(0, -1, +1));
        considerNeighbour(pos, glm::ivec3(0, +1, +1));
        considerNeighbour(pos, glm::ivec3(0, +1, -1));
    }

    return m_neighbours;
}

void VoxelNeighbourHelper::considerNeighbour(const glm::ivec3& pos, const glm::ivec3 &offset) {
    Voxel * neighbour = m_voxelCluster->voxel(pos + offset);
    if(neighbour != nullptr) {
        m_neighbours.push_back(neighbour);
    }
}

