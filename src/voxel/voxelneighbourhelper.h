#pragma once

#include "voxel.h"


class VoxelNeighbourHelper
{
public:
    VoxelNeighbourHelper(Voxel *voxel, bool includeDiagonals = false);

    std::list<Voxel*> neighbours();


protected:
    Voxel *m_voxel;
    bool m_includeDiagonals;
    std::list<Voxel*> m_neighbours;
};
