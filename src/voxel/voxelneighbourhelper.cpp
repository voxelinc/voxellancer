#include "voxelneighbourhelper.h"

#include "geometry/grid3daabb.h"

#include "voxel/voxelcluster.h"


VoxelNeighbourHelper::VoxelNeighbourHelper(VoxelCluster *voxelCluster, Voxel *voxel, bool includeDiagonals):
    m_voxelCluster(voxelCluster),
    m_voxel(voxel),
    m_includeDiagonals(includeDiagonals)
{

}

std::list<Voxel*> VoxelNeighbourHelper::neighbours() {
    m_neighbours.clear();

    considerNeighbour(glm::ivec3(-1, 0, 0));
    considerNeighbour(glm::ivec3(+1, 0, 0));
    considerNeighbour(glm::ivec3(0, -1, 0));
    considerNeighbour(glm::ivec3(0, +1, 0));
    considerNeighbour(glm::ivec3(0, 0, -1));
    considerNeighbour(glm::ivec3(0, 0, +1));

    if(m_includeDiagonals) {
        considerNeighbour(glm::ivec3(-1, -1, -1));
        considerNeighbour(glm::ivec3(-1, +1, -1));
        considerNeighbour(glm::ivec3(+1, +1, -1));
        considerNeighbour(glm::ivec3(+1, -1, -1));
        considerNeighbour(glm::ivec3(-1, -1, +1));
        considerNeighbour(glm::ivec3(-1, +1, +1));
        considerNeighbour(glm::ivec3(+1, +1, +1));
        considerNeighbour(glm::ivec3(+1, -1, +1));
    }

    return m_neighbours;
}

void VoxelNeighbourHelper::considerNeighbour(const glm::ivec3 &relativeCell) {
    glm::ivec3 absoluteCell;
    Voxel *neighbour;

    absoluteCell = m_voxel->gridCell() + relativeCell;

    neighbour = m_voxelCluster()->voxel(absoluteCell);
    if(neighbour != nullptr) {
        m_neighbours.push_back(neighbour);
    }
}

