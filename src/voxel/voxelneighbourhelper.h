#pragma once

#include <vector>
#include <vector>
#include <glm/glm.hpp>


class Voxel;
class VoxelCluster;

class VoxelNeighbourHelper
{
public:
    VoxelNeighbourHelper(VoxelCluster *voxelCluster, bool includeDiagonals = true);

    const std::vector<Voxel*>& neighbours(const glm::ivec3& pos);
    const std::vector<Voxel*>& neighbours(const Voxel* voxel);

    bool hasNeighbour(const glm::ivec3& pos);
    bool hasNeighbour(const Voxel* voxel);


protected:
    VoxelCluster *m_voxelCluster;
    std::vector<Voxel*> m_neighbours;
    bool m_includeDiagonals;

    static std::vector<glm::ivec3> s_directNeighbours;
    static std::vector<glm::ivec3> s_indirectNeighbours;


    void considerNeighbour(const glm::ivec3& pos, const glm::ivec3& offset);
};
