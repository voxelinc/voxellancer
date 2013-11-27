#pragma once

#include <list>

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"


class VoxelClusterOrphan
{
public:
    void addVoxel(Voxel *voxel);
    void addAllVoxels(VoxelClusterOrphan *orphanCluster);

    VoxelCluster *exVoxelCluster();
    void setExVoxelCluster(VoxelCluster *exVoxelCluster);

    glm::ivec3 gridLlf() const;

    std::list<Voxel*> orphanedVoxels();


protected:
    std::list<Voxel*> m_orphanedVoxels;
    VoxelCluster *m_exVoxelCluster = nullptr;
};

