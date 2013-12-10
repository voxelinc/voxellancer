#pragma once

#include <list>

#include "voxel/voxel.h"
#include "voxel/voxelcluster.h"


class WorldObject;

class WorldObjectSplit
{
public:
    void addVoxel(Voxel *voxel);
    void addAllVoxels(WorldObjectSplit *orphanCluster);

    WorldObject *exWorldObject();
    void setExWorldObject(WorldObject *exWorldObject);

    std::list<Voxel*> splitOffVoxels();


protected:
    WorldObject* m_exWorldObject;
    std::list<Voxel*> m_splitOffVoxels;
};

