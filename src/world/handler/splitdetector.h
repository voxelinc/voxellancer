#pragma once

#include <set>
#include <list>

class VoxelClusterOrphan;
class WorldObject;
class Voxel;

class SplitDetector
{
public:
    void searchOrphans(std::set<WorldObject*> &modifiedWorldObject);
    std::list<VoxelClusterOrphan*> &voxelClusterOrphans();


protected:
    std::list<VoxelClusterOrphan*> m_voxelClusterOrphans;
    WorldObject *m_currentWorldObject;

    std::set<Voxel*> m_potentialOrphans;

    void clear();
    void fillPotentialOrphans();
    VoxelClusterOrphan *pollContinuousVoxels(Voxel *orphanVoxel);
};

