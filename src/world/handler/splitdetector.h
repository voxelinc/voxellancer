#pragma once

#include <set>
#include <list>

class VoxelClusterOrphan;
class WorldObject;

class SplitDetector
{
public:
    void searchOrphans(std::set<WorldObject*> &modifiedVoxelClusters);
    std::list<VoxelClusterOrphan*> &voxelClusterOrphans();


protected:
    std::list<VoxelClusterOrphan*> m_voxelClusterOrphans;
};

