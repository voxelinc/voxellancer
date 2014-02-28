#pragma once

#include <list>


class Voxel;
class VoxelCluster;

class VoxelGraveyard {
public:
    VoxelGraveyard(VoxelCluster* voxelCluster);
    virtual ~VoxelGraveyard();

    void bury(Voxel* voxel);
    void revive(Voxel* voxel);

    std::list<Voxel*>& voxels();


protected:
    VoxelCluster* m_voxelCluster;
    std::list<Voxel*> m_voxels;
};

