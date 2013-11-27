#pragma once

#include <list>

class VoxelClusterOrphan;
class WorldObject;

class Splitter
{
public:
    void split(std::list<VoxelClusterOrphan*> &voxelClusterOrphans);
    std::list<WorldObject*> &splitOffVoxelClusters();


protected:
    std::list<WorldObject*> m_splitOffVoxelClusters;
};

