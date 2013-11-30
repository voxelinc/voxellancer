#pragma once

#include <list>

class VoxelClusterOrphan;
class WorldObject;

class Splitter
{
public:
    void split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans);
    std::list<WorldObject*> &splitOffWorldObjects();


protected:
    std::list<WorldObject*> m_splitOffWorldObjects;

    WorldObject *createWorldObjectFromOrphan(VoxelClusterOrphan *orphanCluster);
    void removeExtractedVoxelsFromEx(VoxelClusterOrphan *orphanCluster);
};

