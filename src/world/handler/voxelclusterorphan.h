#pragma once

#include <list>

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"


class WorldObject;

class VoxelClusterOrphan
{
public:
    void addVoxel(Voxel *voxel);
    void addAllVoxels(VoxelClusterOrphan *orphanCluster);

    WorldObject *exWorldObject();
    void setExWorldObject(WorldObject *exWorldObject);

    glm::ivec3 gridLlf() const;

    std::list<Voxel*> orphanedVoxels();


protected:
    WorldObject* m_exWorldObject;
    std::list<Voxel*> m_orphanedVoxels;
};

